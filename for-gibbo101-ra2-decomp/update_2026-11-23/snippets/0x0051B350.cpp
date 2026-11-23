// ra2-decomp help snippet, update 2026-11-23 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0051B350 (1881 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0x101a80 (VA 0x00501A80, 1876 bytes without padding)
// RA2 symbol : ?Tunnel_AI@InfantryClass@@QAEXXZ
// similarity : 0.9260 (similar, masked instruction tokens; shape 0.9991)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/infantry.cpp
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

void InfantryClass::Tunnel_AI(void)
{
	bool finished = Tubes[CurrentTube]->Dirs[CurrentTubeDir] == FACING_NONE;
	if (!finished) {
		int distance = Distance_To_Coord(this, LastTubeCoord); // level-2 1.001: see Distance_To_Coord
		TubeClass * tube = Tubes[CurrentTube];
		DirType direction = Direction_To(this, LastTubeCoord); // level-2 1.001: see Direction_To
		int speed = Class->MaxSpeed;

		// level-2 1.001 (INFERRED block): the mouth coords live only in this block, so they share their slots
		// with the later Move_Coord temporaries; each tube Cell is copied once (one DWORD temporary per statement),
		// and the step count is read after both coords are built
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
				// level-2 1.001: the adjacent coord is a temporary of this statement, not a named local
				LastTubeCoord = LastTubeCoord + ((TPoint2D<int> const &)Map[Adjacent_Cell(LastTubeCoord, tube->Dirs[CurrentTubeDir])].Cell_Coord() - (TPoint2D<int> const &)Map[LastTubeCoord].Cell_Coord());
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
			new_coord.Z += speed / divisor * height_step;
			PositionCoord = new_coord;
			return;
		}
	}

	if (finished) {
		CellClass * cellptr = &Map[Get_Coord()];
		ObjectClass * occupier = cellptr->Cell_Occupier();
		if (Can_Enter_Cell(cellptr, FACING_NONE, 0) != MOVE_OK) {
			// level-2 1.001: the occupiers are collected first, then the idle vehicles and soldiers among them are told to scatter
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
		} else {
			Coord spot = cellptr->Closest_Free_Spot(Get_Coord());
			spot.Z = Map.Get_Height_GL(spot);
			PositionCoord = spot;

			Locomotion->Force_Immediate_Destination(COORD_NONE);
			Locomotion->Stop_Movement_Animation();
			Mark(MARK_DOWN);
			Set_Occupy_Bit(Get_Coord());

			if (NavCom == cellptr) {
				Scatter(Coord(0, 0, 0), true, true);
			} else {
				Set_Speed(1);
			}
			CurrentTube = TUBE_NONE;
			IsPlanningToLook = true;
			Per_Cell_Process(PCP_END);
		}
	}
}
