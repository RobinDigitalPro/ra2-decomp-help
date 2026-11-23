// ra2-decomp help snippet, update 2026-11-23 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00741970 (6167 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0x2fa040 (VA 0x006FA040, 5598 bytes without padding)
// RA2 symbol : ?Assign_Destination@UnitClass@@UAEXPAVAbstractClass@@_N@Z
// similarity : 0.6608 (partial, masked instruction tokens; shape 0.8869)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/unit.cpp
// License    : GPL-3.0-or-later. Our source is GPL and contains EA GPL code (section 7 terms)
//              and code adapted from mischa85/RedAlert2 and gibbo101/ra2-decomp; their
//              credits are kept. The notice of the source file follows. See ../README.md.
// Use        : a read-only lead. RA2 layouts and names; port it and match it on your own checker.

/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2025 Electronic Arts Inc.
 * Copyright 2026 OpenTS contributors
 *
 * Contains material derived from Electronic Arts source code.
 * Modified by OpenTS contributors, 2026.
 * EA's GPLv3 Section 7 additional terms and supplemental warranty
 * disclaimers apply; see LICENSE.md.
 ******************************************************************************/

/***********************************************************************************************
 * UnitClass::Assign_Destination -- Assign a destination to a unit.                            *
 *                                                                                             *
 *    This will assign the specified destination to the unit. It is presumed that doing is     *
 *    is all that is needed in order to cause the unit to move to the specified destination.   *
 *                                                                                             *
 * INPUT:   target   -- The target (location) to move to.                                      *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/09/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
void UnitClass::Assign_Destination(AbstractClass * target, bool immediate)
{
	/*
	**	Abort early if there is anything wrong with the parameters
	**	or the unit already is assigned the specified destination.
	*/
	if (Class->BalloonHover && target == NULL && NavCom != NULL && TarCom != NULL) { // RA2: a hovering balloon unit already chasing its target keeps going
		if (NavCom == TarCom) return; // RA2: as above
		if (Unit_Is_Cell(NavCom)) { // RA2: as above
			CellClass * destination = Unit_As_Cell(NavCom); // RA2: as above
			if (destination->Cell_Occupier() == TarCom) return; // RA2: as above
		}
	}
	if (target == NavCom && !UnlimboingInfantry) return; // RA2: the unlimbo flag lets the same destination through once
	UnlimboingInfantry = false; // RA2: as above
	if (Deployed) { // RA2: a deployed unit only stops
		FootClass::Abort_Motion(); // RA2: as above
		return; // RA2: as above
	}

	/*
	**	Transport vehicles must tell all passengers that are about to load, that they
	**	cannot proceed. This is accomplished with a radio message to this effect.
	*/
	if (HasAnyLink() && Class->Max_Passengers() > 0 && Radio_Link(0)->Fetch_RTTI() == RTTI_INFANTRY) { // RA2: as above
		if (target != NULL && (target->AbstractFlags & 1) && !ContainsLink((TechnoClass *)target)) { // RA2: only when the destination is a techno that is not linked
			Transmit_Message(RADIO_OVER_OUT); // RA2: as above
		}
	}

	/*
	 * If tethered to a carryall while sleeping, untether before moving.
	 */
	if (target != NULL && HasAnyLink() && Get_Mission() == MISSION_SLEEP && IsTethered && Radio_Link(0)->Fetch_RTTI() == RTTI_AIRCRAFT) { // RA2: as above
		AircraftClass * a = (AircraftClass *)Radio_Link(0); // RA2: as above
		if (a->Class->IsCarryall) {
			a->Assign_Destination(NULL, true); // RA2: as above
			Transmit_Message(RADIO_UNTETHER);
			Transmit_Message(RADIO_OVER_OUT);
		}
	}

	BuildingClass * b = Unit_As_Building(target); // RA2: the inline RTTI-tested cast, not dynamic_cast
	if (Get_Mission() == MISSION_UNLOAD || MissionQueue == MISSION_UNLOAD) { // RA2: a refinery being unloaded into loses its dump effects
		Cell unload_cell = Get_Cell() + AdjacentCell[6]; // RA2: as above
		BuildingClass * refinery = (BuildingClass *)Map[unload_cell].Cell_Building(); // RA2: as above
		if (refinery != NULL && Class->IsToHarvest) { // RA2: as above
			if (refinery->ParticleSystems[5] != NULL) refinery->ParticleSystems[5]->Delete_Me(); // RA2: as above
			if (refinery->ParticleSystems[6] != NULL) refinery->ParticleSystems[6]->Delete_Me(); // RA2: as above
			if (refinery->Anims[10] != NULL) refinery->End_Anim((BAnimType)10); // RA2: as above
		}
	}

	/*
	**	Handle entry logic here.
	*/
	if (Get_Mission() == MISSION_ENTER || MissionQueue == MISSION_ENTER) { // RA2: as above

		/*
		**	If not already in radio contact (presumed with the transport), then
		**	either try to establish contact if allowed, or just move close and
		**	wait until radio contact can be established.
		*/
		if (!HasAnyLink()) { // RA2: as above
			TechnoClass * destination_techno = Dynamic_Cast<TechnoClass *>(target); // RA2: as above
			if (destination_techno != NULL && destination_techno->Fetch_RTTI() == RTTI_UNIT) { // RA2: a unit destination is queued up behind
				QueueUpToEnter = Unit_As_Unit(target); // RA2: as above
				ArchiveTarget = NULL; // RA2: as above
				target = NULL; // RA2: as above
			} else if (b != NULL && b->Fetch_RTTI() == RTTI_BUILDING) { // RA2: as above

				/*
				**	Determine if the transport is already in radio contact. If so, then just move
				**	toward the transport and try to establish contact at a later time.
				*/
				if (b->HasAnyLink()) { // RA2: as above
					ArchiveTarget = target;

					/*
					**	HACK ALERT: The repair bay is counting on the assignment of the NavCom by this routine.
					**	The refinery must NOT have the navcom assigned by this routine.
					*/
					if (b->Class->IsCanUnitRepair) {
						target = NULL; // level-2 1.001: every unit queues up for the repair bay (no health test)
						QueueUpToEnter = b; // level-2 1.001: as above
					}
				} else {
					AbstractClass * oldnav = NavCom;
					if (Transmit_Message(RADIO_DOCKING, b) != RADIO_ROGER) {
						Transmit_Message(RADIO_OVER_OUT);
						if (b->Class->IsCanUnitRepair) {
							ArchiveTarget = target;
						}
					} else {
						if (b->Class->IsDockUnload && NavCom != oldnav) {
							target = NavCom;
						}
					}
				}
			} else {
				TechnoClass * techno = (target != NULL && (target->AbstractFlags & 1)) ? (TechnoClass *)target : NULL; // RA2: the inline flag-tested techno cast
				if (techno != NULL) {

					/*
					**	Determine if the transport is already in radio contact. If so, then just move
					**	toward the transport and try to establish contact at a later time.
					*/
					if (techno->HasAnyLink()) { // RA2: as above
						ArchiveTarget = target;
					} else {
						if (Transmit_Message(RADIO_HELLO, techno) == RADIO_ROGER) {
							if (Transmit_Message(RADIO_DOCKING) != RADIO_ROGER) { // RA2: the handshake continues after a successful docking message
								Transmit_Message(RADIO_OVER_OUT); // RA2: as above
							}
						}
					}
				}
			}
		} else {
			Path[0] = FACING_NONE;
		}
	} else {
		Path[0] = FACING_NONE;
	}

	bool useplan = false;

	/*
	 * Subterranean units prepend their navigation target onto the queue and
	 * re-target the nearest reachable cell when driving rather than burrowing.
	 */
	if (target != NULL && Class->IsSubterranean && Locomotion->Is_Moving()) {
		IPersistPtr persist(Locomotion);
		CLSID clsid;
		persist->GetClassID(&clsid);
		if (clsid == CLSID_DriveLocomotion) {
			NavQueue.Add_Head(target);
			RouteQueue.Clear();
			CellClass * tcell = Get_Target_Cell_Ptr();
			target = tcell;
			immediate = false;
			if (tcell != NULL && tcell->IsUnderBridge && !Is_Moving_Onto_Bridge()) {
				Cell nearby = Map.Nearby_Location(tcell->CellID, SPEED_TRACK, Map.Get_Cell_Zone(tcell->CellID, Class->MZone, false), Class->MZone, false, Point2D(1, 1), false, true, false, false);
				if (nearby != CELL_NONE) {
					target = &Map[nearby];
				}
			}
		}
	}

	bool needsswap = false;

	if (target != NULL) {
		bool surface = false;

		/*
		 * A subterranean unit that is told to move immediately must decide whether
		 * it can burrow straight to the destination or has to plan a surface route.
		 */
		if (Class->IsSubterranean && immediate) {
			bool isbridge = Is_Moving_Onto_Bridge();

			Cell from = Destination_Coord().As_Cell();
			bool canburrowfrom = Map[from].Can_Burrow_Here();

			Cell to = target->Center_Coord().As_Cell();
			CellClass * tocell = &Map[to];
			bool isunderbridgeto = tocell->IsUnderBridge;
			bool canburrowto = tocell->Can_Burrow_Here();
			int height = Get_Height_AGL();

			if (isbridge && isunderbridgeto) { // RA2: one condition
				int z1 = Map.Zone_Connection_Index(from, 3, 0); // RA2: as above
				if (z1 == Map.Zone_Connection_Index(to, 3, 0) && z1 != -1) { // RA2: as above
					if (!Map.ZoneConnections[z1].IsPassable) { // RA2: as above
						Cell d1 = Map.Get_Zone_Connection_Destination(from, from); // RA2: as above
						Cell d2 = Map.Get_Zone_Connection_Destination(to, to); // RA2: as above
						if ((d1 - d2).Length() <= 2) { // RA2: the cell difference is measured inline
							needsswap = true;
						}
					} else {
						needsswap = true; // RA2: as above
					}
				}
			}
			if ((isbridge || isunderbridgeto) && !needsswap) { // RA2: the plan decision is two separate tests
				useplan = true; // RA2: as above
			}

			if (((!canburrowfrom && height >= 0) || !canburrowto) && !needsswap) { // RA2: as above
				useplan = true; // RA2: as above
			}
		}

		if (useplan) { // RA2: the plan is made here, the immediate branch is separate
			target = Plan_Route(target); // RA2: as above
			surface = true; // RA2: as above
		} else if (immediate) { // RA2: as above
			RouteQueue.Clear(); // RA2: as above
			surface = true; // RA2: as above
		}

		/*
		 * Surfacing tunneler keeps its current cell at the route front.
		 */
		if (surface) {
			if (Locomotion->Is_Surfacing()) {
				RouteQueue.Add_Head(target);
				target = &Map[Get_Coord()];
			}
		}

	} else {
		RouteQueue.Clear(); // RA2: as above
	}

	if (Class->Teleporter && !IsImmobilized) { // RA2: a teleporting unit may need a drive locomotor to enter a dock
		TechnoClass * contact = Radio_Link(0); // RA2: as above
		IPersistPtr persist(Locomotion); // RA2: as above
		CLSID tclsid; // RA2: as above
		persist->GetClassID(&tclsid); // RA2: as above
		bool drive = true; // RA2: as above
		if (contact != NULL) { // RA2: as above
			if (contact->Fetch_RTTI() == RTTI_BUILDING) { // RA2: as above
				BuildingClass * building = Unit_As_Building(contact); // RA2: as above
				CellClass * cell = Unit_As_Cell(target); // RA2: as above
				if (building->Class->IsDockUnload && cell != NULL && cell->Cell_Unit(false) == NULL) { // RA2: as above
					drive = false; // RA2: as above
					if (!(tclsid == CLSID_TeleportLocomotion)) { // RA2: as above // RA2: as above
						IPiggybackPtr piggy(Locomotion); // RA2: as above
						if (piggy != NULL && piggy->Is_Piggybacking() && piggy->Is_Ok_To_End()) { // RA2: as above
							piggy->End_Piggyback(&Locomotion); // RA2: as above
						} else {
							Locomotion->Stop_Moving(); // RA2: as above
							Set_Mission(MISSION_NONE); // RA2: as above
							QueueMission(MISSION_ENTER, false); // RA2: as above
							IsMoveToSkipped = true; // RA2: as above
							UnlimboingInfantry = true; // RA2: as above
						}
					}
				}
			}
		}
		if ((contact == NULL || drive == true) && !(tclsid == CLSID_DriveLocomotion)) { // RA2: as above
			IPiggybackPtr piggy(Locomotion); // RA2: as above
			if (piggy != NULL && piggy->Is_Piggybacking() && piggy->Is_Ok_To_End()) { // RA2: as above
				piggy->End_Piggyback(&Locomotion); // RA2: as above
			}
			ILocomotionPtr walk(CLSID_DriveLocomotion); // RA2: as above
			walk->Link_To_Object(this); // RA2: as above
			piggy = IPiggybackPtr(walk); // RA2: as above
			if (piggy != NULL) { // RA2: as above
				piggy->Begin_Piggyback(Locomotion); // RA2: as above
				Locomotion = walk; // RA2: as above
			}
		}
	}

	/*
	 * If the locomotor is a tunnel locomotor and the unit is on the ground,
	 * surface the tunneler by swapping the tunnel locomotor for a drive one.
	 * (Mirrors BuildingClass weapons-factory exit, building.cpp:6236-6251.)
	 */
	if (target != NULL && !Locomotion->Is_Moving()) { // RA2: as above
		IPersistPtr persist(Locomotion); // RA2: as above
		CLSID clsid; // RA2: as above
		persist->GetClassID(&clsid); // RA2: as above
		if (clsid == CLSID_TunnelLocomotion && Get_Height_AGL() == 0) { // RA2: as above
			Coord tc = target->Center_Coord(); // RA2: as above
			int gl = Map.Get_Height_GL(tc); // RA2: as above
			if (tc.Z < gl) tc.Z = gl; // RA2: as above

			bool doswap = needsswap; // RA2: as above
			if (!doswap) { // RA2: as above
				bool canburrow = !Is_Moving_Onto_Bridge() // RA2: as above
					&& !Map[target->Center_Coord()].IsUnderBridge // RA2: as above
					&& Map[Destination_Coord()].Can_Burrow_Here() // RA2: as above
					&& Map[target->Center_Coord()].Can_Burrow_Here(); // level-2 1.001: one full expression stored in a bool, so each Coord temporary keeps its own slot
				if (canburrow) {
					if (!Is_Route_Broken(Get_Target_Cell(), target->Center_Coord().As_Cell())) { // level-2 1.001: one full expression (no named Cell local)
						doswap = true; // RA2: as above
					}
				} else {
					doswap = true; // RA2: as above
				}
			}

			if (doswap) { // RA2: as above
				IPiggybackPtr piggy(Locomotion); // RA2: as above
				if (piggy != NULL && piggy->Is_Piggybacking()) { // RA2: as above
					piggy->End_Piggyback(&Locomotion); // RA2: as above
				}
				ILocomotionPtr walk(CLSID_DriveLocomotion); // RA2: as above
				walk->Link_To_Object(this); // RA2: as above
				{
					IPiggybackPtr walk_piggy(walk); // RA2: the drive locomotor's piggyback interface is a named local
					piggy = (IPiggyback *)walk_piggy; // RA2: as above
				}
				if (piggy != NULL) { // RA2: as above
					piggy->Begin_Piggyback(Locomotion); // RA2: as above
					Locomotion = walk; // RA2: as above
					Locomotion->Force_New_Slope(Map[Get_Coord()].Ramp); // RA2: as above
				}
			}
		}
	}

	/*
	**	If the player clicked on a friendly repair facility and the repair
	**	facility is currently not involved with some other unit (radio or unloading).
	*/
	if (b != NULL && b->Class->IsCanUnitRepair) {
		if (b->HasAnyLink() && b->Radio_Link(0) != this) { // RA2: as above
			ArchiveTarget = target;
		} else {

			/*
			**	Establish radio contact protocol. If the facility responds correctly,
			**	then remain in radio contact and proceed toward the desired destination.
			*/
			if (Transmit_Message(RADIO_HELLO, b) == RADIO_ROGER) {
				if (Transmit_Message(RADIO_DOCKING) == RADIO_ROGER) {
					BASECLASS::Assign_Destination(target, immediate);
					Path[0] = FACING_NONE;
					return;
				}

				/*
				**	Failure to establish a docking relationship with the refinery.
				**	Bail & await further instructions.
				*/
				Transmit_Message(RADIO_OVER_OUT);
				target = NULL;
			}
		}
	}

	/*
	 * A weapons factory that this unit is exiting wants the unit driven to its
	 * exit cell before anything else; queue the real destination behind it.
	 */
	BuildingClass * wf = (BuildingClass *)Radio_Link(0); // RA2: as above
	if (wf != NULL && wf->Fetch_RTTI() == RTTI_BUILDING && wf->Class->IsWeaponsFactory && CurrentMission != MISSION_ENTER) { // RA2: not while entering
		Cell exitcell = wf->Get_Coord().As_Cell() + Cell(5, 1); // RA2: RA2's exit cell is (5, 1)
		if (target != &Map[exitcell]) {
			NavQueue.Clear();
			RouteQueue.Clear();
			if (target != NULL) {
				Queue_Navigation_List(target);
			}
			return;
		}
	}

	/*
	 * Harvesters and weeders automatically enter their dock building when the
	 * clicked target is that building (and the houses are allied).
	 */
	if (b != NULL && Class->Dock.Count() > 0 && Unit_Is_Dock(Class, b->Class) && // level-2 1.001: any dock type
		Fetch_RTTI() == RTTI_UNIT && (Class->IsToHarvest || Class->IsToVeinHarvest) &&
		Get_Mission() != MISSION_UNLOAD) { // RA2: no ally test

		if (Radio_Link(0) != b && !b->HasAnyLink() && Transmit_Message(RADIO_HELLO, b) == RADIO_ROGER && // RA2: as above
			Get_Mission() != MISSION_ENTER && Get_Mission() != MISSION_HARVEST) { // RA2: as above
			QueueMission(MISSION_ENTER, false); // RA2: QueueMission replaces Assign_Mission
			target = NULL;
		} else {
			if (target != NULL && target->Fetch_RTTI() == RTTI_BUILDING && Radio_Link(0) != target) { // RA2: as above
				Cell nearby = Map.Nearby_Location(b->Get_Coord().As_Cell(), SPEED_WHEEL, Map.Get_Cell_Zone(b->Get_Coord().As_Cell(), Class->MZone, false), Class->MZone, false, Point2D(1, 1), false, true, false, false);
				if (nearby != CELL_NONE) {
					target = &Map[nearby];
				} else {
					target = NULL;
				}
			}
		}
	}

	/*
	 * If the locomotor is unpowered and we are not in an ion storm, power it
	 * back on when an adjacent friendly repair facility occupies our cell.
	 */
	if (!Locomotion->Is_Powered() && !House->Ion_Sensitives_Should_Be_Offline()) { // RA2: the house's ion test
		CellClass * cellptr = Get_Cell_Ptr();
		if (!cellptr->IsUnderBridge) {
			ObjectClass * occupier = cellptr->Cell_Occupier();
			while (occupier != NULL) {
				if (occupier != this && occupier->Fetch_RTTI() == RTTI_BUILDING && ((BuildingClass *)occupier)->Class->IsCanUnitRepair) {
					Locomotion->Power_On();
					break;
				}
				occupier = occupier->Next;
			}
		}
	}

	BASECLASS::Assign_Destination(target, immediate);
}
