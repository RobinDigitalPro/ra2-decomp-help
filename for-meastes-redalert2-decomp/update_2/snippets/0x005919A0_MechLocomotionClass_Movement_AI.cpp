// RA2 1.001 byte-identical (VC6 8168 /O2 /Ob2 /Gr /GR /Gy), RVA 0x18e7a0, from our src/m85/src/mech.cpp. GPL-3.0-or-later.
// Your 1.006 entry 0x005919A0 (MechLocomotionClass::Movement_AI, 5575 bytes, non_exact in your map).

void MechLocomotionClass::Movement_AI(bool continue_moving)
{
	if (LinkedTo->PrimaryFacing.Is_Rotating()) {
		return;
	}

	if (HeadToCoord == COORD_NONE) {
		if (DestinationCoord != COORD_NONE) {

			if (LinkedTo->Path[0] == FACING_NONE) {

				if (LinkedTo->PathDelay != 0) {
					LinkedTo->Stop_Movement_Animation();
					return;
				}

				LinkedTo->PathDelay = Rule->PathDelay * TICKS_PER_MINUTE;

				if (!LinkedTo->Basic_Path(DestinationCoord.As_Cell(), 0, 0)) {

					if (!LinkedTo->Is_In_Same_Zone(DestinationCoord)) {
						LinkedTo->Assign_Destination(NULL);
						return;
					}

					int dist = Distance(LinkedTo->Center_Coord(), DestinationCoord);

					if (dist < (int)Rule->CloseEnoughDistance && !LinkedTo->IsTethered) {
						LinkedTo->Assign_Destination(NULL);
					} else {

						if (LinkedTo->TryTryAgain != 0) {
							LinkedTo->TryTryAgain--;
						} else {

							if (LinkedTo->IsNewNavCom) {
								Sound_Effect(Rule->ScoldSound);
							}
							LinkedTo->IsNewNavCom = false;

							Cell dest_cell = DestinationCoord;
							if (LinkedTo->IsLocked) {
								Cell src_cell = LinkedTo->Destination_Coord().As_Cell();
								if (!Map.Is_Same_Cell_Zone(src_cell, dest_cell, LinkedTo->TClass->MZone, LinkedTo->Is_Moving_Onto_Bridge(), Map[dest_cell].IsUnderBridge, LinkedTo->Is_Allowed_To_Leave_Map())) {
									LinkedTo->Assign_Destination(NULL);
								}
							}

							if (LinkedTo->TarCom != NULL) {
								Cell tar_cell = LinkedTo->TarCom->Destination_Coord(LinkedTo).As_Cell();
								if (LinkedTo->IsLocked) {
									Cell src_cell = LinkedTo->Destination_Coord(LinkedTo).As_Cell();
									if (!Map.Is_Same_Cell_Zone(src_cell, tar_cell, LinkedTo->TClass->MZone, LinkedTo->Is_Moving_Onto_Bridge(LinkedTo), Map[tar_cell].IsUnderBridge, LinkedTo->Is_Allowed_To_Leave_Map())) {
										LinkedTo->Assign_Target(NULL);
									}
								}
							}
						}
					}

					LinkedTo->Set_Speed(0);
					Stop_Moving();
					IsMoving = false;
					return;
				}

				LinkedTo->TryTryAgain = FootClass::PATH_RETRY;
			}

			FacingType dir = LinkedTo->Path[0];
			if (dir == FACING_COUNT) {

				int tube = Map[LinkedTo->Get_Coord()].Tube;
				if (tube >= 0 && tube < Tubes.Count()) {
					LinkedTo->Mark(MARK_UP);
					LinkedTo->Clear_Occupy_Bit(LinkedTo->Get_Coord());

					TubeClass * tubeptr = Tubes[tube];

					HeadToCoord = Coord(Cell(tubeptr->Exit), 0); // level-2 1.001: STEERING keep a separate exit cell for the coordinate conversion

					memcpy(&LinkedTo->Path[0], &LinkedTo->Path[1], sizeof(LinkedTo->Path[0]) * (CONQUER_PATH_MAX - 1));
					LinkedTo->Path[CONQUER_PATH_MAX - 1] = FACING_NONE;

					LinkedTo->CurrentTube = tube;
					TPoint2D<short> const & enter = tubeptr->Enter; // level-2 1.001: STEERING use the entrance point to construct the two cell operands
					LinkedTo->CurrentTubeDir = FACING_FIRST;

					Coord offset = Map[Adjacent_Cell(Cell(enter), tubeptr->Dirs[0])].Cell_Coord() - Coord(Cell(enter)); // level-2 1.001: STEERING form the entrance offset before adding the unit position
					LinkedTo->LastTubeCoord = offset + LinkedTo->Get_Coord();

					int start_h = Map.Get_Height_GL(LinkedTo->Get_Coord());
					LinkedTo->LastTubeCoord.Z = start_h + Tube_Height_Step(Cell(tubeptr->Exit), tubeptr->Count, start_h); // level-2 1.001: STEERING preserve the exit cell temporary at the height call
					return;
				}

				LinkedTo->Path[0] = FACING_NONE;
				HeadToCoord = COORD_NONE;
				Stop_Moving();
				LinkedTo->Assign_Destination(NULL);
				return;
			} else {
				Cell what = Adjacent_Cell(LinkedTo->Get_Coord().As_Cell(), dir);

				Coord head_coord = Coord(what, 0);
				head_coord.Z = Map.Get_Height_GL(head_coord);

				CellClass * what_cell = &Map[what];

				if (LinkedTo->IsOnBridge ^ what_cell->IsUnderBridge) {
					LinkedTo->IsPlanningToLook = true;
				}

				MoveType can_enter = LinkedTo->Can_Enter_Cell(&Map[what], dir, LinkedTo->Get_Cell_Height(), 0, true);

				if (((can_enter != MOVE_DESTROYABLE && can_enter != MOVE_FRIENDLY_DESTROYABLE) || !LinkedTo->TClass->IsCrusher || what_cell->Overlay != OVERLAY_FIRST) && can_enter != MOVE_OK) {

					LinkedTo->Stop_Movement_Animation();

					if (can_enter == MOVE_TEMP) {

						CellClass * cellptr = &Map[what];

						if (continue_moving) {
							LinkedTo->Path[0] = FACING_NONE;
							HeadToCoord = COORD_NONE;
							LinkedTo->PathDelay = 0;
							Movement_AI(false);
							return;
						}

						int dist = LinkedTo->Distance(DestinationCoord);

						if (dist < (int)Rule->CloseEnoughDistance && !LinkedTo->HasAnyLink()
							&& abs(DestinationCoord.Z - LinkedTo->Get_Coord().Z) < 2 * LEVEL_LEPTON_H
							&& Map[LinkedTo->Get_Coord()].Land_Type() != LAND_TUNNEL) {

							LinkedTo->Set_Speed(0);
							LinkedTo->Assign_Destination(NULL);
							LinkedTo->Path[0] = FACING_NONE;
							Stop_Moving();
							IsMoving = false;
						} else {

							bool bridge = cellptr->IsUnderBridge && abs(LinkedTo->Get_Coord().Z / LEVEL_LEPTON_H - cellptr->Height) > 2;
							cellptr->Incoming(COORD_NONE, true, true, bridge);
						}
						return;
					}

					if (can_enter == MOVE_MOVING_BLOCK) {

						if (!LinkedTo->IsToPathAroundBlockage) {
							LinkedTo->IsToPathAroundBlockage = true;
							LinkedTo->BlockagePathDelay = Rule->BlockagePathDelay;
						}

						if (LinkedTo->PathDelay == 0) {

							bool blockage_expired = LinkedTo->IsToPathAroundBlockage && LinkedTo->BlockagePathDelay == 0;

							bool path_ok = LinkedTo->Basic_Path(DestinationCoord.As_Cell(), 0, blockage_expired ? 2 : 1);
							LinkedTo->PathDelay = Rule->PathDelay * TICKS_PER_MINUTE;

							if (!path_ok) {
								if (!LinkedTo->Is_In_Same_Zone(DestinationCoord)) {
									LinkedTo->Assign_Destination(NULL);
								} else {
									LinkedTo->On_Movement_Blocked();
								}
							} else {
								LinkedTo->JumpJet_To_Walk();
							}
							return;
						}

						DirStruct face = (DirStruct &)::Direction(LinkedTo->Center_Coord(), head_coord);
						Do_Turn(face);
						return;
					}

					if (can_enter == MOVE_CLOSED_GATE) {
						Map.Try_Open_Gate(LinkedTo, what);
						LinkedTo->TryTryAgain = FootClass::PATH_RETRY;
						return;
					}

					if (can_enter != MOVE_CLOAK && can_enter != MOVE_NO) {
						if (can_enter == MOVE_DESTROYABLE || can_enter == MOVE_FRIENDLY_DESTROYABLE) {

							ObjectClass * obj = Map[what].Cell_Object(Point2D(0, 0), false);

							if (continue_moving) {
								LinkedTo->Path[0] = FACING_NONE;
								HeadToCoord = COORD_NONE;
								LinkedTo->PathDelay = 0;
								Movement_AI(false);
								return;
							}

							if (obj != NULL) {
								if (!LinkedTo->House->Is_Ally(obj)) {
									LinkedTo->Override_Mission(MISSION_ATTACK, obj, 0);
								}
							} else {
								if (Map[what].Overlay != OVERLAY_NONE && OverlayTypes[Map[what].Overlay]->IsWall) {
									LinkedTo->Override_Mission(MISSION_ATTACK, &Map[what], 0);
								}
							}
						}

						LinkedTo->Path[0] = FACING_NONE;
						LinkedTo->Set_Speed(0);
						Stop_Moving();
						LinkedTo->IsNewNavCom = false;
					} else {
						if (can_enter == MOVE_CLOAK) {
							Map[what].Shimmer();
						}

						if (!continue_moving) return;

						LinkedTo->Path[0] = FACING_NONE;
						HeadToCoord = COORD_NONE;
						LinkedTo->PathDelay = 0;
						Movement_AI(false);
						return;
					}
				} else {

					if (Mark_Head_To(head_coord)) {

						if (LinkedTo->Path[0] != FACING_NONE && LinkedTo->Path[0] != FACING_COUNT) {
							Cell cell = Adjacent_Cell(LinkedTo->Get_Cell(), LinkedTo->Path[0]);
							CellClass * cellptr = &Map[cell];
							if (cellptr->Overlay != OVERLAY_NONE) {
								OverlayTypeClass * otype = OverlayTypes[cellptr->Overlay];
								if ((LinkedTo->TClass->IsCrusher || LinkedTo->Has_Ability(ABILITY_CRUSHER)) && otype->HeapID == OVERLAY_SANDBAG_WALL) {
									LinkedTo->IsCrushing = true;
									if (LinkedTo->TClass->IsTiltsWhenCrushes) {
										LinkedTo->RockingForwardsPerFrame = -0.01f;
									}
								}
							}
						}

						if (!LinkedTo->IsActive) return;

						DirStruct face = (DirStruct &)::Direction(LinkedTo->Center_Coord(), HeadToCoord);
						Do_Turn(face);

						if (LinkedTo->PrimaryFacing.Is_Rotating()) return;

						LinkedTo->Set_Speed(1.0);
					} else {
						LinkedTo->Set_Speed(0);
					}
				}
			}

		} else {

			if (LinkedTo->Speed > 0.0) {
				LinkedTo->Set_Speed(0.0);
			}
		}
	} else {

		if (Distance(Point2D(LinkedTo->Center_Coord()), Point2D(HeadToCoord)) < 16) {

			LinkedTo->Mark(MARK_UP);

			if (LinkedTo->Path[0] == FACING_NONE) {
				LinkedTo->Path[1] = FACING_NONE;
			}

			memcpy(&LinkedTo->Path[0], &LinkedTo->Path[1], sizeof(LinkedTo->Path[0]) * (CONQUER_PATH_MAX - 1));
			LinkedTo->Path[CONQUER_PATH_MAX - 1] = FACING_NONE;

			LinkedTo->Set_Coord(HeadToCoord);
			LinkedTo->LastPathingCell = HeadToCoord.As_Cell();
			LinkedTo->HeightAGL = 0;

			Mark_Head_To(COORD_NONE);

			if (LinkedTo->Path[0] == FACING_NONE) {
				LinkedTo->Set_Speed(0);
			}

			LinkedTo->IsOccupyingCell = true;

			LinkedTo->IsToPathAroundBlockage = false;

			if (DestinationCoord == COORD_NONE
				|| (LinkedTo->Get_Cell() == DestinationCoord.As_Cell()
					&& abs(LinkedTo->Destination_Coord().Z - DestinationCoord.Z) < 2 * LEVEL_LEPTON_H)) {

				LinkedTo->Assign_Destination(NULL);
				LinkedTo->Set_Speed(0.0);
				Stop_Moving();
				IsMoving = false;
			}

			LinkedTo->Per_Cell_Process(PCP_END);

			if (!LinkedTo->IsActive) return;
			if (LinkedTo->IsInLimbo || LinkedTo->IsFalling) return;

			if (LinkedTo->Path[0] != FACING_NONE && LinkedTo->Path[0] != FACING_COUNT) {
				Cell check_coord = Adjacent_Cell(LinkedTo->Get_Cell(), LinkedTo->Path[0]);

				CellClass * cellptr = &Map[check_coord];
				if (cellptr->Overlay != OVERLAY_NONE) {
					OverlayTypeClass * otype = OverlayTypes[cellptr->Overlay];
					if ((LinkedTo->TClass->IsCrusher || LinkedTo->Has_Ability(ABILITY_CRUSHER)) && otype->HeapID == OVERLAY_SANDBAG_WALL) {
						LinkedTo->IsCrushing = true;

						if (LinkedTo->TClass->IsTiltsWhenCrushes) {
							LinkedTo->RockingForwardsPerFrame = -0.01f;
						}
					}
				}
			}

			if (!LinkedTo->IsActive || LinkedTo->IsInLimbo) return;

			LinkedTo->Mark(MARK_DOWN);
		} else {

			LinkedTo->Set_Speed(1.0);

			int speed = LinkedTo->Current_Speed();

			DirType desired_facing = ::Direction(LinkedTo->Center_Coord(), HeadToCoord);
			Do_Turn((DirStruct &)desired_facing);

			if (LinkedTo->PrimaryFacing.Is_Rotating()) {
				return;
			}

			if (LinkedTo->Occupies_Cells()) {
				LinkedTo->Clear_Occupy_Bit(LinkedTo->Get_Coord());
				LinkedTo->IsOccupyingCell = false;
				LinkedTo->IsToPathAroundBlockage = false;
			}

			Cell old_cell = LinkedTo->Get_Cell();

			Coord new_coord = Move_Coord(LinkedTo->Get_Coord(), desired_facing, speed);
			Cell new_cell = new_coord;

			bool moved = (old_cell != new_cell);
			if (moved) {
				LinkedTo->Mark(MARK_UP);
				LinkedTo->Set_Coord(new_coord);

				CellClass * old_cellptr = &Map[old_cell];
				CellClass * new_cellptr = &Map[new_cell];

				if (new_cellptr->Height == old_cellptr->Height - BRIDGE_CELL_HEIGHT && new_cellptr->IsUnderBridge) {
					LinkedTo->IsOnBridge = true;
				}
				if (!new_cellptr->IsUnderBridge && old_cellptr->IsUnderBridge) {
					LinkedTo->IsOnBridge = false;
				}

				LinkedTo->HeightAGL = 0;
				LinkedTo->Mark(MARK_DOWN);
			} else {
				bool was_down = LinkedTo->IsDown;
				LinkedTo->IsDown = false;
				LinkedTo->Set_Coord(new_coord);
				LinkedTo->HeightAGL = 0;
				LinkedTo->IsDown = was_down;
			}

			if (moved) {
				Map[LinkedTo->Get_Coord()].Trigger_Veins();
			}
		}
	}
	LinkedTo->IsNewNavCom = false;
}
