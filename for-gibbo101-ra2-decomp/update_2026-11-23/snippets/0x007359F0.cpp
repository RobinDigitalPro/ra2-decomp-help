// ra2-decomp help snippet, update 2026-11-23 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007359F0 (1730 bytes; gibbo101/ra2-decomp name: UnitClass::UpdateTube)
// RA2 address: RVA 0x2ef6d0 (VA 0x006EF6D0, 1727 bytes without padding)
// RA2 symbol : ?Tunnel_AI@UnitClass@@QAEXXZ
// similarity : 0.9349 (similar, masked instruction tokens; shape 0.9981)
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

void UnitClass::Tunnel_AI(void)
{
	bool finished = Tubes[CurrentTube]->Dirs[CurrentTubeDir] == FACING_NONE;
	if (!finished) {
		int distance = Distance_To_Coord(this, LastTubeCoord); // level-2 1.001: see Distance_To_Coord
		TubeClass * tube = Tubes[CurrentTube];
		Get_Coord();	/// Result discarded.

		DirType direction = Direction_To(this, LastTubeCoord); // level-2 1.001: see Direction_To
		int speed = (int)(Class->MaxSpeed * 1.5);

		// level-2 1.001 (INFERRED block): as in InfantryClass::Tunnel_AI, the mouth coords live only in this block,
		// each tube Cell is copied once into one DWORD temporary, and the step count is read after both coords
		int height_step;
		{
			Coord exit(Cell(tube->Exit));
			Coord enter(Cell(tube->Enter));
			int count = tube->Count;
			height_step = (Map.Get_Height_GL(exit) - Map.Get_Height_GL(enter)) / count;
		}

		if (distance <= speed) {
			CurrentTubeDir++;
			FacingType tube_dir = tube->Dirs[CurrentTubeDir];
			finished = tube_dir == FACING_NONE;
			PositionCoord = LastTubeCoord;

			if (!finished) {
				Coord delta = Map[Unit_Tube_Adjacent_Coord(LastTubeCoord, tube_dir)].Cell_Coord() - Map[LastTubeCoord].Cell_Coord(); // level-2 1.001: the adjacent coord is a temporary
				LastTubeCoord = LastTubeCoord + TPoint2D<int>(delta.X, delta.Y); // level-2 1.001: all three members are stored back
				LastTubeCoord.Z += height_step;

				DirType dir = Direction_To(this, LastTubeCoord); // level-2 1.001: as above
				Coord new_coord = Move_Coord(PositionCoord, dir, speed - distance);
				double divisor;
				if (tube_dir % 2) {
					divisor = CELL_LEPTON_H * M_SQRT2;
				} else {
					divisor = CELL_LEPTON_H;
				}
				new_coord.Z += (speed - distance) / divisor * height_step;
				PositionCoord = new_coord;
				return;
			}
		} else {
			FacingType tube_dir = tube->Dirs[CurrentTubeDir];
			Coord new_coord = Move_Coord(Get_Coord(), direction, speed);
			double divisor;
			if (tube_dir % 2) {
				divisor = CELL_LEPTON_H * M_SQRT2;
			} else {
				divisor = CELL_LEPTON_H;
			}
			new_coord.Z += (speed) / divisor * height_step;
			PositionCoord = new_coord;
			return;
		}
	}

	if (finished) {
		CellClass * cellptr = &Map[Get_Coord()];
		ObjectClass * occupier = cellptr->Cell_Occupier();

		// level-2 1.001: with anything in the exit cell, every occupier is collected first, the idle
		// vehicles and soldiers among them are told to scatter, and the unit waits in the tube
		if (occupier != NULL) {
			DynamicVectorClass<ObjectClass *> occupiers;
			while (occupier != NULL) {
				occupiers.Add(occupier);
				occupier = occupier->Next;
			}

			for (int index = 0; index < occupiers.Count(); index++) {
				ObjectClass * object = occupiers[index];
				if (object->RTTI == RTTI_UNIT || object->RTTI == RTTI_INFANTRY) {
					if (!((FootClass *)object)->Locomotion->Is_Moving()) {
						object->Scatter(Coord(0, 0, 0), true, true);
					}
				}
			}

			Set_Speed(0);
			return;
		} else { // level-2 1.001: the arrival path is its own block (its exit coord shares the temporaries' slot)

			TubeClass * tube = Tubes[CurrentTube];
			Cell exit_cell = tube->Exit;
			Coord exit_coord(exit_cell, LastTubeCoord.Z);
			PositionCoord = exit_coord;
			CurrentTube = TUBE_NONE;

			Mark(MARK_DOWN); // level-2 1.001: always marked down

			if (NavCom == cellptr) {
				Scatter(Coord(0, 0, 0), true, true);
			}

			IsPlanningToLook = true;
			Per_Cell_Process(PCP_END);
			Set_Speed(1);

			TubeClass * tube_here = Map[Get_Coord()].Get_Tunnel();
			if (tube_here != NULL) {
				PrimaryFacing.Set(DirType((FacingType)(tube_here->EnterDir - 4)).Snap_To_8()); // level-2 1.001: the facing opposite to the tube's entry
			}
		}
	}
}
