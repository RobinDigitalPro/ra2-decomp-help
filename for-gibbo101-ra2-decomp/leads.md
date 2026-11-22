# Leads for functions gibbo101/ra2-decomp has attempted but not matched

All RA2 sources below are byte-identical on RA2 1.001 `GAME.EXE` (VC6, `/O2 /Ob2 /Gr /GR`). They are leads, not matches. YR adds fields and branches, and gibbo's toolchain uses the SP3 code generator (`C2.DLL` 12.00.8447) where we use the RTM one (12.00.8168), so every idea still has to pass gibbo's checker on `gamemd.exe`.

## 1. UnitClass::Do_MISSION_HARVEST (YR 0x0073E5E0, 2528 bytes; gibbo 99.9%)

**Gibbo's blocker** (attempts.csv, 2026-11-12 to 2026-11-21): x87 load scheduling. The inlined `Distance_To(nearest)` in the ChronoHarvTooFarDistance arm (exe 0x73EDF9) emits `fild` Y,Z,X, where the exe has X,Y,Z. In their builds it follows the layout (whichever TooFar arm comes after the retry block), not the source text. Only `Distance(nearest->Center_Coord())` in that arm gave the right order, and it cost +12 bytes of frame.

**Ours:** RA2 0x2F7220 (VA 0x6F7220), 2496 bytes, byte-identical. Source TU: `src/m85/src/unit.cpp`. Masked token similarity with YR 0x0073E5E0 is 0.82 (shape 0.93). That is below the pairing threshold because the YR body differs in places, but the FINDHOME block has the same layout.

**The three distance computations** (`fild` order and frame slots in both executables):

| Site | RA2 1.001 | YR 1.001 |
|---|---|---|
| HarvesterTooFarDistance arm | 0x6F77DB: X `[esp+38]`, Y `[esp+3C]`, Z `[esp+40]` | 0x73EBC7: X, Y, Z (same slots) |
| retry `> 3 * CELL_LEPTON` | 0x6F78AE: Y, Z, X | 0x73EC9A: Y, Z, X |
| ChronoHarvTooFarDistance arm | 0x6F7A0C: X, Y, Z | 0x73EDF9: X, Y, Z |

The offsets from the function start differ by 0x2C (harvester arm +0x5BB against +0x5E7, chrono arm +0x7EC against +0x819). The order and layout are identical, so the RA2 source form is a direct candidate.

**What gives this order in our source** (see the full source below):
- **Both TooFar arms use one TU-local helper chain, not `Distance_To`.**
  - `Unit_Distance_ZYX(this, nearest)` builds the delta of the two `Center_Coord()` values with `Unit_Coord_Delta`.
  - It then takes `Unit_Length_ZYX`: `(int)fastmath::sqrt((double)c.Z*c.Z + (double)c.Y*c.Y + (double)c.X*c.X)`. The sum is written Z, Y, X, the conversions are done in place, and there are no named double locals.
  - VC6 loads the right-hand terms first, so this gives `fild` X, Y, Z in BOTH arms, whatever their layout.
- **Only the retry keeps `Distance_To(nearest) > 3 * CELL_LEPTON_W`.** Its inline gives the Y, Z, X order.
- **The two arms are one condition:** `((!teleporter && nearest && D <= HarvesterTooFar*256) || (teleporter && nearest && D <= ChronoHarvTooFar*256)) && Transmit_Message(RADIO_HELLO, nearest) == RADIO_ROGER`.
- **`bool teleporter = Class->Teleporter;`** is read once before the switch.
- **The helper uses `Center_Coord()` of both objects.** The `this` side is not `Coord` / `PositionCoord`. That is consistent with gibbo's observation that only `Distance(nearest->Center_Coord())` moved the order.
  - Our helper reaches it through a separate `Coord` delta temporary, so the frame stays at 1.001's size.
  - The delta is passed by `const &` to an inline. Its 12-byte temporary is the `[esp+38..40]` triple in both executables.
- **Not tested on YR:** whether this form also gives YR's frame and the rest of the 2528 bytes. Two things are untested:
  - YR's extra code (its body is 32 bytes longer; we have not diffed what it adds);
  - the different code generator.

**Our full source** (unit.cpp; the three helpers sit directly above the function):

```cpp

/// <summary>
/// RA2: the distance between two objects' centers, summed z, y, x (Do_MISSION_HARVEST's refinery distance limits)
/// </summary>
static inline Coord Unit_Coord_Delta(Coord const & a, Coord const & b) // RA2: as above
{
	return Coord(a.X - b.X, a.Y - b.Y, a.Z - b.Z); // RA2: as above
}

static inline int Unit_Length_ZYX(Coord const & coord) // RA2: as above
{
	return((int)fastmath::sqrt((double)coord.Z * coord.Z + (double)coord.Y * coord.Y + (double)coord.X * coord.X)); // RA2: as above; level-2 1.001: converted in place, no double locals (x87 order of the second expansion)
}

static inline int Unit_Distance_ZYX(ObjectClass const * from, ObjectClass const * to) // RA2: as above
{
	return(Unit_Length_ZYX(Unit_Coord_Delta(from->Center_Coord(), to->Center_Coord()))); // RA2: as above
}


/***********************************************************************************************
 * UnitClass::Mission_Harvest -- Handles the harvesting process used by harvesters.            *
 *                                                                                             *
 *    This is the AI process used by harvesters when they are doing their harvesting action.   *
 *    This entails searching for nearby Tiberium, heading there, harvesting, and then          *
 *    returning to a refinery for unloading.                                                   *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  Returns with the delay before calling this routine again.                          *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/18/1994 JLB : Created.                                                                 *
 *   06/21/1995 JLB : Force guard mode if no Tiberium found.                                   *
 *   09/28/1995 JLB : Aborts harvesting if there are no more refineries.                       *
 *=============================================================================================*/
int UnitClass::Do_MISSION_HARVEST(void)
{
	int i;

	enum {
		LOOKING,
		HARVESTING,
		FINDHOME,
		HEADINGHOME,
		GOINGTOIDLE,
	};

	/*
	**	A non-harvesting type unit will just sit still if it is given the harvest mission. This
	**	allows combat units to act "brain dead".
	*/
	if (!Class->IsToHarvest && !Class->IsToVeinHarvest) return(TICKS_PER_SECOND*30);

	if (Class->Dock.Count() == 0 && !House->Is_Human_Player()) {
		QueueMission(MISSION_GUARD, false); // RA2: queued, not assigned
		return(1);
	}

	/*
	**	If there are no more refineries, then drop into guard mode.
	*/
	bool found = false; // RA2: the search for an owned dock building is written out with a flag
	for (i = 0; i < Class->Dock.Count(); i++) { // RA2: as above
		if (House->BQuantity.Value(Class->Dock[i]->HeapID) > 0) { // RA2: as above
			found = true; // RA2: as above
			break; // RA2: as above
		}
	}
	if (!found) { // RA2: as above
		QueueMission(MISSION_GUARD, false); // RA2: as above
		return(1); // RA2: as above
	}

	bool teleporter = Class->Teleporter; // RA2: a chrono harvester uses its own distance limit and always looks for a queueing spot
	switch (Status) {

		/*
		**	Go and find a Tiberium field to harvest.
		*/
		case LOOKING:
			if (!Class->IsToVeinHarvest && Tiberium_Load() >= 1.0) { // RA2: a weed harvester has no full check here
				Status = FINDHOME; // RA2: as above
				return(1); // RA2: as above
			}

			{
				/*
				**	Look for ore where we last found some - mine the same patch
				*/
				bool hastarget = true;
				if (ArchivedTarget != NULL) { // RA2: as above
					Assign_Destination(ArchivedTarget, true); // RA2: as above
					Assign_Archive_Target(NULL); // RA2: as above
					hastarget = false;
				}
				IsHarvesting = false;
				bool ok; // RA2: as above
				if (Class->IsToVeinHarvest) {
					ok = Goto_Weed(Rule->TiberiumLongScan / CELL_LEPTON_W);
				} else {
					IPersistPtr persist(Locomotion); // RA2: a chrono harvester drops its destination before it looks for ore
					CLSID clsid; // RA2: as above
					persist->GetClassID(&clsid); // RA2: as above
					if (clsid == CLSID_TeleportLocomotion && NavCom != NULL) { // RA2: as above
						Assign_Destination(NULL, true); // RA2: as above
					}
					ok = Goto_Tiberium(Rule->TiberiumLongScan / CELL_LEPTON_W, hastarget);
				}
				if (ok) {
					IsHarvesting = true;
					Set_Rate(2);
					Set_Stage(0);
					Status = HARVESTING;
					return(1);
				}

				/*
				**	If the harvester isn't on Tiberium and it is not heading toward Tiberium, then
				**	force it to go into guard mode. This will prevent the harvester from repeatedly
				**	searching for Tiberium.
				*/
				if (NavCom == NULL) { // RA2: as above

					/*
					**	If the archive target is legal, then head there since it is presumed
					**	that the archive target points to the last place it harvested at.
					*/
					if (ArchivedTarget != NULL) { // RA2: as above
						Assign_Destination(ArchivedTarget, true); // RA2: as above
					} else {
						Status = GOINGTOIDLE; // RA2: as above
						IsUseless = true; // RA2: as above
						if (Class->IsToHarvest) { // RA2: as above
							House->IsTiberiumShort = true; // RA2: as above
						}
						return(TICKS_PER_SECOND*7); // RA2: as above
					}
				} else {
					IsUseless = false; // RA2: as above
				}
			}
			break;

		/*
		**	Harvest at current location until full or Tiberium exhausted.
		*/
		case HARVESTING:
			if (Fetch_Rate() == 0) {
				Set_Stage(0);
				Set_Rate(Rule->HarvesterLoadRate);
			}

			if (Fetch_Stage() < ARRAY_SIZE(Harvester_Load_List)+1) return(1);
			if (!Harvesting()) {
				IsHarvesting = false;
				if (Class->IsToHarvest && Tiberium_Load() == 1.0) { // RA2: only a Tiberium harvester checks for a full load here
					Status = FINDHOME;
					Cell cell;
					if (Class->IsToHarvest) {
						cell = Search_For_Tiberium(Rule->TiberiumShortScan / CELL_LEPTON_W);
					} else {
						cell = Search_For_Weed(Rule->TiberiumShortScan / CELL_LEPTON_W);
					}
					if (cell != CELL_NONE) {
						Assign_Archive_Target(&Map[cell]); // RA2: as above
					} else {
						Assign_Archive_Target(NULL); // RA2: as above
					}
					return(1); // RA2: as above
				}
				bool ok; // RA2: as above
				if (Class->IsToHarvest) { // RA2: as above
					ok = Goto_Tiberium(Rule->TiberiumShortScan / CELL_LEPTON_W, false); // RA2: as above
				} else {
					ok = Goto_Weed(Rule->TiberiumShortScan / CELL_LEPTON_W); // RA2: as above
				}
				if (!ok && NavCom == NULL)	{ // RA2: as above
					Assign_Archive_Target(NULL); // RA2: as above
					Status = FINDHOME; // RA2: as above
				} else {
					Status = HARVESTING; // RA2: as above
					IsHarvesting = true; // RA2: as above
				}
				return(1);
			}
			return(1);

		/*
		**	Find and head to refinery.
		*/
		case FINDHOME:
			if (NavCom != NULL && teleporter && TryNearestDockBuilding((TypeList<BuildingTypeClass *> *)&Class->Dock, 0, 0) != NULL) { // RA2: a chrono harvester that can dock somewhere stops its walk first
				Abort_Motion(); // RA2: as above
			}
			if (NavCom == NULL) {

				/*
				**	Find nearby refinery and head to it?
				*/
				BuildingClass * nearest = TryNearestDockBuilding((TypeList<BuildingTypeClass *> *)&Class->Dock, 0, 0); // RA2: the whole Dock list at once

				/*
				**	Since the refinery said it was ok to load, establish radio
				**	contact with the refinery and then await docking orders.
				*/
				if (((!teleporter && nearest != NULL && Unit_Distance_ZYX(this, nearest) <= Rule->HarvesterTooFarDistance * 256) || (teleporter && nearest != NULL && Unit_Distance_ZYX(this, nearest) <= Rule->ChronoHarvTooFarDistance * 256)) && Transmit_Message(RADIO_HELLO, nearest) == RADIO_ROGER) { // RA2: a refinery within the harvester's own limit is asked first
					Status = HEADINGHOME;
				} else {
					ScenarioInit++;
					nearest = TryNearestDockBuilding((TypeList<BuildingTypeClass *> *)&Class->Dock, 0, 1); // RA2: as above
					ScenarioInit--;
					if (nearest != NULL) {
						if (Distance_To(nearest) > 3 * CELL_LEPTON_W || teleporter) { // RA2: a chrono harvester always goes to the queueing spot
							Cell cell = Cell(nearest->Get_Coord()); // RA2: as above
							Cell queue = cell; // RA2: the queueing spot is the building's cell plus the type's queueing offset
							queue.X = nearest->Class->QueueingCell.X + cell.X; // RA2: as above
							queue.Y += nearest->Class->QueueingCell.Y; // RA2: as above
							queue = Map.Nearby_Location(queue, SPEED_WHEEL, -1, MZONE_NORMAL, false, Point2D(1, 1), false, false, false, true, Cell(0, 0), false); // RA2: as above
							if (!(queue == CELL_NONE)) { // RA2: as above
								Assign_Destination(&Map[queue], true); // RA2: as above
							} else {
								Assign_Destination(NULL, true); // RA2: as above
							}
						}
					}
				}
			}
			break;

		/*
		**	In communication with refinery so that it will successfully dock and
		**	unload. If, for some reason, radio contact was lost, then hunt for
		**	another refinery to unload at.
		*/
		case HEADINGHOME:
			QueueMission(MISSION_ENTER, false); // RA2: queued, not assigned
			return(1);

		/*
		**	The harvester has nothing to do. There is no Tiberium nearby and
		**	no where to go.
		*/
		case GOINGTOIDLE:
			if (IsUseless) {
				if (House->BQuantity.Value(Rule->RepairBay->HeapID) > 0) {
					QueueMission(MISSION_REPAIR, false); // RA2: as above
				} else {
					QueueMission(MISSION_HUNT, false); // RA2: as above
				}
			}
			{
				BuildingClass * bptr = Map[(Coord const &)PositionCoord].Cell_Building(); // RA2: as above
				if (bptr != NULL) { // RA2: as above
					if (bptr->Class->IsRefinery || bptr->Class->IsWeeder) { // RA2: as above
						Assign_Destination(&Map[Nearby_Location(bptr)], true); // RA2: as above
					}
				}
			}
			QueueMission(MISSION_GUARD, false); // RA2: as above
			break;

	}
	return(Current_Mission_Control().Normal_Delay() + Random_Pick(0, 2));
}
```

## 2. Other gibbo partials that pair with a matched RA2 function

These come from pairs.csv: the rows whose gibbo_status is attempted-partial. Similarity is over masked instruction tokens, and the snippet files hold our full source of each function. The blockers are quoted in short form from gibbo's attempts.csv, latest row.

| YR address | gibbo best | Ours (RA2 RVA) | Similarity | Gibbo's blocker | What we know from RA2 |
|---|---|---|---|---|---|
| 0x007A2330 Setup_Match_Map | 99.1% | Setup_Match_Map 0x349dd0 | 0.853 similar | register choice in the inlined `DynamicVectorClass<MultiMission*>::Add`: ours `add ecx,eax; push ecx`, the exe `add eax,ecx; push eax` | In unit Plan_Route the same `add`/`push` choice of the inlined DynamicVectorClass::Add flipped with a `DynamicVectorClass<T> & route = ...` reference, against using the member directly (vc6_rules.md, R14). Snippet: snippets/0x007A2330.cpp |
| 0x00598960 Generate_Random_Map | 98.4% | MapGeneratorClass::Generate_Random_Map 0x176ec0 | 0.948 similar | inline budget: in the third inlined Cleanup copy the exe calls Delete_Index and VectorClass<Cell>::Clear out of line | The budget is spent from the end of the function (COUNT rule, R1). Our body is byte-identical; compare its later statements with yours. Snippet: snippets/0x00598960.cpp |
| 0x0056D100 MapClass::Is_Same_Cell_Zone | 93.5% | 0x14cc50 | 0.894 similar | tail registers (exe this=esi, mzone=edi, tozone=ebp) | Snippet: snippets/0x0056D100.cpp |
| 0x0060F4B0 OwnerDraw::Subclass_Dialog | 93.4% | 0x1e4da0 | 0.971 very similar | inline budget: in the second inlined SetUserData2 copy, ~WinData stays a call | We match with gibbo's own named-node `~WinData` loop (`TextNode *node = Nodes; Remove_Node(node);`), which weighs like two budget statements (R9). Snippet: snippets/0x0060F4B0.cpp |
| 0x0056C510 MapClass::Zone_Reset | 91.5% | 0x14c060 | 0.934 similar | nzone homed in esi outside the flood-fill loop; the exe keeps it only in `[esp+0x20]` | Snippet: snippets/0x0056C510.cpp |
| 0x007359F0 UnitClass::Tunnel_AI | 70.9% | 0x2ef6d0 | 0.939 similar | stack-slot layout (scope-based lifetimes of address-taken locals) and inline budget | Matched after a long slot study (R6, R7, R14, R15): `Coord exit(Cell(tube->Exit));`; the mouth coords as named locals of an inner block; a separate spilled `int count = tube->Count;`; the code after `if (occupier) {...; return;}` as an `else` block; and a unit-local Adjacent_Cell helper with `Point2D const & offset = AdjacentPoint[i];`. Snippet: snippets/0x007359F0.cpp |
| 0x0051B350 InfantryClass::Tunnel_AI | 69.1% | 0x101a80 | 0.935 similar | stack-slot layout plus a forced single-use _Distance helper | Same study as unit Tunnel_AI; infantry uses the shared Adjacent_Cell inline. Snippet: snippets/0x0051B350.cpp |
| 0x0076D3A0 WorldDominationTour::Selection::Select_Territory_At | 65.3% | 0x323210 | 0.961 very similar | a never-read conditional-temporary flag slot, produced only by the forced `true ? ... : rc_ptr<Territory>()` form | RA2 1.001 has the same artefact. We accept that form as the original's (`rc_ptr<Territory> territory = true ? WorldMap->Get_Territory(id) : rc_ptr<Territory>();`), because the dead flag store is in the executable. Snippet: snippets/0x0076D3A0.cpp |
| 0x0076D180 ...::Handle_Click | 100% (held) | 0x322ff0 | 1.000 exact masked | held: needs the same forced conditional | Exact masked equal to our matched body, which uses the same form. Snippet: snippets/0x0076D180.cpp |
| 0x00624460 OwnerDraw::CellData::~CellData | 100% (held) | 0x1f90c0 | 1.000 exact masked | emitted only by its unmatched caller ListBoxHandler 0x00618D40 | On our side it is a compiler-generated destructor with no source text, emitted by ownrdraw.cpp. No snippet. It confirms gibbo's reading: it appears once the TU that emits it matches. |
| 0x00492830 BlitTransLucent50<unsigned short>::Blit_Forward | 24% (failed) | 0x86e60 | 1.000 exact masked | hand-written inline asm that no EA source release contains | We agree that it is hand-written assembly. Our byte-identical RA2 copy is an explicit `template<>` specialization with an `__asm` body (src/ra2/templates/BLIT_INSTANCES.cpp), and it may fit gibbo's `src/ra2asm/` RECONSTRUCTED category. The snippet is left out of this package because it is an inline-asm reconstruction; it is available on request. |

## 3. Shared open problems (stuck on both sides)

- **WaveClass::Build_Wave_Shape** (RA2 0x318470, 2368 bytes, about 27 bytes off) and **YR Draw_NonMagnetic**: the same two scheduling spots on both sides.
  - At +0x431 the early `lea esi` / `push esi` of `&WaveStartMiddle` comes before the EndCoord stores.
  - At +0x597 the start_right copy is scheduled against the dz integer work.
  - Neutral for us: the Count order, constructor-form vectors and a named `Point2D &`. Worse: an early distance2d_f, dz moved earlier, EndCoord before PositionCoord.
- **Init_Voxel_Matrices** (RA2 0x30cc20, 3290 bytes, 25 bytes off; YR 0x00754CB0, gibbo 97.0%): mirror images of one problem.
  - We have an esi/edi swap of the zero / `i*12` web against `&LightDirectionVectors[i]`.
  - Gibbo has the right registers with TibSun's all-reference loop, but one `[esi+4]` load is 3 bytes short.
  - Neutral for us: references at the loop top, `Matrix3D(true)`, `i < 256`, an inline theta and an indexed tilt_matrix operand.

If either side solves one of these, the other side probably can too.
