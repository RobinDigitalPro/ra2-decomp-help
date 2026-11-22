// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0051B350 (1881 bytes; gibbo status: attempted-partial 69.1%)
// RA2 RVA    : 0x101a80 (VA 0x00501A80, 1888 bytes incl. padding)
// RA2 symbol : ?Tunnel_AI@InfantryClass@@QAEXXZ
// similarity : 0.9349 (similar, masked instruction tokens; shape 0.9885)
// source TU  : src/m85/src/infantry.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

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
