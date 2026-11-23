// ra2-decomp help snippet, update 2026-11-23 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004B0F20 (5892 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0xa0d20 (VA 0x004A0D20, 5736 bytes without padding)
// RA2 symbol : ?While_Moving@DriveLocomotionClass@@AAE_N_N@Z
// similarity : 0.7695 (partial, masked instruction tokens; shape 0.9262)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/drive.cpp
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
 * DriveClass::While_Moving -- Processes unit movement.                                        *
 *                                                                                             *
 *    This routine is used to process movement for the units as they move.                     *
 *    It is called many times for each cell's worth of movement.   This                        *
 *    routine only applies after the next cell HeadTo has been determined.                     *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  true/false; Should this routine be called again?                                   *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   02/02/1992 JLB : Created.                                                                 *
 *   04/15/1994 JLB : Converted to member function.                                            *
 *=============================================================================================*/
bool DriveLocomotionClass::While_Moving(bool just_started)
{
	assert(LinkedTo->IsActive);

	/*
	**	Perform quick legality checks.
	*/
	if ((!IsDriving || TrackNumber == -1) && LinkedTo->Path[0] != FACING_COUNT || (IsRotating && !LinkedTo->TClass->IsTurretEquipped)) {
		SpeedAccum = 0;		// Kludge?  No speed should accumulate if movement is on hold.
		return(false);
	}
	if (LinkedTo->TClass->IsAccelerates) {
		bool not_passive = LinkedTo->RTTI != RTTI_UNIT || !((UnitClass *)LinkedTo)->Class->IsPassive;
		if (TrackNumber < BACKUP_INTO_REFINERY && not_passive) {
			Coord dest_coord = DestinationCoord;
			dest_coord.Z = Map.Get_Height_GL(dest_coord) + (Map[dest_coord].IsUnderBridge ? BRIDGE_LEPTON_HEIGHT : 0);
			int distance = (LinkedTo->PositionCoord - dest_coord).Length();//LinkedTo->PositionCoord.Distance_To(dest_coord);

			bool forced_speed = false;
			double speed = LinkedTo->Speed;

			TechnoTypeClass const * tclass = LinkedTo->TClass;
			int maxspeed = LinkedTo->Get_Max_Speed();

			if (distance < tclass->SlowdownDistance) {
				forced_speed = true;
				speed = MAX(_deaccel, speed - maxspeed * tclass->DeaccelerationFactor);
			} else if (LinkedTo->IsSinking) {
				speed = MAX(_sinking, speed - maxspeed * _sinking_scale);
				forced_speed = true;
			}

			if (LinkedTo->IsCrushing) {
				TargetSpeed = MIN(TargetSpeed, 0.2);
				LinkedTo->Set_Speed(TargetSpeed);
			} else if (forced_speed) {
				LinkedTo->Set_Speed(speed);
			} else if (LinkedTo->Speed < TargetSpeed) {
				LinkedTo->Set_Speed(MIN(TargetSpeed, LinkedTo->Speed + tclass->AccelerationFactor));
			} else if (LinkedTo->Speed > TargetSpeed) {
				LinkedTo->Set_Speed(MAX(TargetSpeed, LinkedTo->Speed - maxspeed * tclass->DeaccelerationFactor));
			}

			if (LinkedTo->RTTI == RTTI_UNIT) {
				UnitClass * following = ((UnitClass *)LinkedTo)->FollowingMe;
				if (following != NULL) {
					do {
						following->Set_Speed(LinkedTo->Speed);
						following = following->FollowingMe;
					} while (following && following != following->FollowingMe);
				}
			}
		}
	} else {
		LinkedTo->Set_Speed(TargetSpeed);
	}

	/*
	**	If enough movement has accumulated so that the unit can
	**	visibly move on the map, then process accordingly.
	**	Slow the unit down if he's carrying a flag.
	*/
	int maxspeed = LinkedTo->Current_Speed();
	//if (IsFormationMove) maxspeed = FormationMaxSpeed;

	int actual;			// Working movement addition value.
	actual = SpeedAccum + (just_started ? 0 : maxspeed); // RA2: the speed accumulation comes before the next facing is read

	FacingType		nextface;		// Next facing queued in path. // RA2: declared after actual
	nextface = LinkedTo->Path[0]; // RA2: as above

	if (nextface == FACING_COUNT && TrackNumber == -1) {
		LinkedTo->Mark(MARK_UP);
		Stop_Driver();

		TubeType tubenum = (TubeType)LinkedTo->Get_Cell_Ptr()->Tube;
		if (tubenum >= TUBE_FIRST && tubenum < Tubes.Count()) {
			TubeClass * tube = Tubes[tubenum];
			Cell c = tube->Exit;
			HeadToCoord = c.As_Coord();
			memcpy((char*)&LinkedTo->Path, (char*)&LinkedTo->Path[1], sizeof(LinkedTo->Path[0]) * (CONQUER_PATH_MAX-1));
			LinkedTo->Path[CONQUER_PATH_MAX-1] = FACING_NONE;
			LinkedTo->CurrentTube = tubenum;
			TPoint2D<short> const & enter = tube->Enter; // RA2: the entry point is held in a reference before the tube direction is set
			LinkedTo->CurrentTubeDir = FACING_FIRST;
			LinkedTo->LastTubeCoord = Map[Adjacent_Cell(Cell(enter), tube->Dirs[0])].Cell_Coord(); // RA2: as above
			int current_height = Map.Get_Height_GL(LinkedTo->PositionCoord);
			Cell exit = tube->Exit; // RA2: the exit cell is a new local, read before the count
			int count = tube->Count;
			LinkedTo->LastTubeCoord.Z = current_height + (Map.Get_Height_GL(exit) - current_height) / count; // RA2: uses the new local
			IsDriving = true;
			TrackNumber = -1;
		} else {
			LinkedTo->Path[0] = FACING_NONE;
			TrackNumber = -1;
			HeadToCoord = COORD_NONE;
			Stop_Driver();
		}
		return(false);
	}

	if (actual > ((PIXEL_LEPTON_W + PIXEL_LEPTON_H) / 2)) {
		TurnTrackType	const * track;  // Track control pointer.
		TrackType		const	* ptr;  // Pointer to coord offset values.
		int				tracknum;       // The track number being processed.
		bool				adj;        // Is a turn coming up?

		track = &TrackControl[TrackNumber];
		if (IsOnShortTrack) {
			tracknum = track->StartTrack;
		} else {
			tracknum = track->Track;
		}
		ptr = RawTracks[tracknum-1].Track;
		//nextface = LinkedTo->Path[0];

		if (nextface < FACING_NONE || nextface > FACING_COUNT) {
			LinkedTo->Path[0] = FACING_NONE;
			return(false);
		}

		/*
		**	Determine if there is a turn coming up. If there is
		**	a turn, then track jumping might occur.
		*/
		adj = false;
		if (nextface != FACING_COUNT && nextface != FACING_NONE && Dir_Facing(track->Facing) != nextface) {
			adj = true;
		}

		/*
		**	Skip ahead the number of track steps required (limited only
		**	by track length). Set the unit to the new position and
		**	flag the unit accordingly.
		*/
		//LinkedTo->Mark(MARK_UP);
		while (actual > (PIXEL_LEPTON_W + PIXEL_LEPTON_H) / 2) {
			Point2D	offset;
			Dir256	dir;

			actual -= (PIXEL_LEPTON_W + PIXEL_LEPTON_H) / 2;

			offset = ptr[TrackIndex].Offset;
			if (offset != Point2D(0, 0) || !TrackIndex) {
				if (LinkedTo->Occupies_Cells()) {
					LinkedTo->Clear_Occupy_Bit(LinkedTo->PositionCoord);
					LinkedTo->IsOccupyingCell = false;
					LinkedTo->IsToPathAroundBlockage = false;
				}

				Cell oldcell;
				if (!TrackIndex) {
					oldcell = LinkedTo->PositionCell;
				} else {
					dir = ptr[TrackIndex - 1].Facing;
					Point2D prevoffset = ptr[TrackIndex - 1].Offset;
					oldcell = Coord(Smooth_Turn(prevoffset, dir), 0).As_Cell();
				}

				dir = ptr[TrackIndex].Facing;
				Coord newcoord = Coord(Smooth_Turn(offset, dir), 0);
				Cell newcoord_cell = newcoord.As_Cell(); // level-2 1.001: both cells are read into locals before the comparison (as in ship.cpp)
				Cell linked_coord_cell = LinkedTo->PositionCoord.As_Cell(); // level-2 1.001: as above
				Cell newcell = newcoord.As_Cell();

				if (newcoord_cell != linked_coord_cell) { // level-2 1.001: as above
					LinkedTo->Mark(MARK_UP);
					LinkedTo->PositionCoord = newcoord;
					CellClass * oldcellptr = &Map[oldcell];
					CellClass * newcellptr = &Map[newcell];
					if (newcellptr->Height == oldcellptr->Height - BRIDGE_CELL_HEIGHT && newcellptr->IsUnderBridge) {
						LinkedTo->IsOnBridge = true;
					}
					if (!newcellptr->IsUnderBridge && oldcellptr->IsUnderBridge) {
						LinkedTo->IsOnBridge = false;
					}
					UnitClass * train; // level-2 1.001: the unit is held in a local across the crush loop
					if (LinkedTo->TClass->IsTrain && !(train = (UnitClass *)LinkedTo)->IsFollowing) { // level-2 1.001: as above
						bool is_bridge = train->IsOnBridge || (LinkedTo->PositionCoord.Z >= (Map.Get_Height_GL(LinkedTo->PositionCoord) + BRIDGE_LEPTON_HEIGHT));
						ObjectClass * occupier = is_bridge
							? Map[newcell].Cell_Bridge_Occupier()
							: Map[newcell].Cell_Occupier(false);
						while (occupier != NULL) {
							ObjectClass * next = occupier->Next;
							if (!occupier->Class_Of()->IsCrushable) {
								int strength = 10000;
								occupier->Take_Damage(strength, 0, Rule->C4Warhead, NULL, true, true);
								strength = 20;
								train->Take_Damage(strength, 0, Rule->C4Warhead, NULL, true, false); // level-2 1.001: as above
							}
							occupier = next;
						}
					}
					if (!LinkedTo->IsActive) return(false);
					LinkedTo->Mark(MARK_DOWN);

					if (newcellptr->Overlay != OVERLAY_NONE) {
						OverlayTypeClass * otype = OverlayTypes[newcellptr->Overlay];
						if (IsRocking && (LinkedTo->TClass->IsCrusher || LinkedTo->Has_Ability(ABILITY_CRUSHER)) && otype->HeapID == OVERLAY_SANDBAG_WALL) {
							LinkedTo->IsCrushing = true;
							if (LinkedTo->TClass->IsTiltsWhenCrushes) {
								LinkedTo->RockingForwardsPerFrame = -0.02f;
							}
						}
					}
				} else {
					bool down = LinkedTo->IsDown;
					LinkedTo->IsDown = false;
					LinkedTo->PositionCoord = newcoord;
					LinkedTo->IsDown = down;
				}

				if (!LinkedTo->IsActive) {
					return(false);
				}

				bool down = LinkedTo->IsDown;
				LinkedTo->IsDown = false;
				LinkedTo->HeightAGL = 0;
				LinkedTo->IsDown = down;

				LinkedTo->PrimaryFacing.Set(dir);

				/*
				**	See if "per cell" processing is necessary.
				*/
				if (TrackIndex && RawTracks[tracknum-1].Cell == TrackIndex) {
					LinkedTo->Clear_Occupy_Bit(LinkedTo->PositionCoord);
				}

				/*
				**	The unit could "jump tracks". Check to see if the unit should
				**	do so.
				*/
				if (nextface != FACING_COUNT && nextface != FACING_NONE && adj && RawTracks[tracknum-1].Jump == TrackIndex && TrackIndex) {
					TurnTrackType const * newtrack;		// Proposed jump-to track.
					int	tnum;

					tnum = DirType(track->Facing).As_Dir8() * FACING_COUNT + nextface;
					newtrack = &TrackControl[tnum];
					if (newtrack->Track && RawTracks[newtrack->Track-1].Entry) {
						double oldspeed = LinkedTo->Speed;

						Coord c = Adjacent_Cell(HeadToCoord, nextface);

						switch (LinkedTo->Can_Enter_Cell(&Map[c.As_Cell()], nextface, LinkedTo->Get_Cell_Height())) {
							case MOVE_OK:
							case MOVE_MOVING_BLOCK:
								if (LinkedTo->RTTI == RTTI_UNIT && !((UnitClass *)LinkedTo)->Class->IsPassive) break;
								IsOnShortTrack = false;		// Shouldn't be necessary, but...
								TrackNumber = tnum;
								track = newtrack;

								tracknum = track->Track;
								TrackIndex = RawTracks[tracknum-1].Entry-1;	// Anticipate increment.
								ptr = RawTracks[tracknum-1].Track;
								adj = false;

								Stop_Driver();
								IsDriving = true;
								LinkedTo->Per_Cell_Process(PCP_END);
								IsDriving = false;
								if (!LinkedTo->IsActive || LinkedTo->IsInLimbo || LinkedTo->IsFalling) return(false); // level-2 1.001: no LinkedTo == NULL test
								if (Start_Driver(c)) {
									LinkedTo->Set_Speed(oldspeed);
									memcpy((char*)&LinkedTo->Path, (char*)&LinkedTo->Path[1], sizeof(LinkedTo->Path[0]) * (CONQUER_PATH_MAX-1));
									LinkedTo->Path[CONQUER_PATH_MAX-1] = FACING_NONE;
								}
								break;

							case MOVE_CLOAK:
								Map[c].Shimmer();
								break;

							case MOVE_CLOSED_GATE: {
								Cell gate = c.As_Cell();
								Map.Try_Open_Gate(LinkedTo, gate);
								break;
							}

							case MOVE_TEMP: {
									bool bridge;
									if (!Map[c].IsUnderBridge || abs(LinkedTo->PositionCoord.Z / LEVEL_LEPTON_H - Map[c].Height) <= 2) {
										bridge = false;
									} else {
										bridge = true;
									}
									Map[HeadToCoord].Incoming(COORD_NONE, true, true, bridge);
								}
								break;
						}
					}
				}
				TrackIndex++;

			} else {
				Coord dc = HeadToCoord - LinkedTo->PositionCoord;
				int d = abs(dc.X) + abs(dc.Y);
				actual += (int)((1.0 - (double)d / 11.0) * 7.0);
				LinkedTo->IsOccupyingCell = true;
				LinkedTo->IsToPathAroundBlockage = false;

				Cell poscell = LinkedTo->PositionCoord.As_Cell();
				if (poscell != HeadToCoord.As_Cell()) {
					LinkedTo->Mark(MARK_UP);
					LinkedTo->PositionCoord = HeadToCoord;
					LinkedTo->HeightAGL = 0;
					LinkedTo->Mark(MARK_DOWN);
				} else {
					bool down = LinkedTo->IsDown;
					LinkedTo->IsDown = false;
					LinkedTo->PositionCoord = HeadToCoord;
					LinkedTo->HeightAGL = 0;
					LinkedTo->IsDown = down;
				}

				//actual = 0;
				//DestinationCoord = Head_To_Coord();
				Stop_Driver();
				TrackNumber = -1;
				TrackIndex = NULL;

				bool arrived = false;
				if (LinkedTo->NavCom != NULL && LinkedTo->PositionCell == LinkedTo->NavCom->Destination_Coord(LinkedTo).As_Cell()) {
					if (abs(LinkedTo->Destination_Coord(LinkedTo).Z - DestinationCoord.Z) < 2 * LEVEL_LEPTON_H) {
						arrived = true;
						DestinationCoord = COORD_NONE;
						Stop_Driver();
						IsDriving = false;
					}
				}

				/*
				**	Perform "per cell" activities.
				*/
				//LinkedTo->Mark(MARK_DOWN);
				LinkedTo->Per_Cell_Process(PCP_END);
				if (!LinkedTo->IsActive || LinkedTo->IsInLimbo || LinkedTo->IsFalling) return(true); // level-2 1.001: no LinkedTo == NULL test
				//LinkedTo->Mark(MARK_UP);

				if (arrived) {
					LinkedTo->Abort_Motion(); // level-2 1.001: not just NavCom = NULL (0x4cd5b0)
					LinkedTo->Path[0] = FACING_NONE;
					if (LinkedTo->Mission == MISSION_MOVE && LinkedTo->Enter_Idle_Mode()) {
						return(true);
					}
				}

				if (LinkedTo->Is_Docked_For_Repair()) {
					return(true);
				}

				if (!LinkedTo->IsActive) return(false);

				break;
			}
		}
		// if (LinkedTo->IsActive) {
		// 	LinkedTo->Mark(MARK_DOWN);
		// }
	}

	/*
	**	Replace any remainder back into the unit's movement
	**	accumulator to be processed next pass.
	*/
	SpeedAccum = actual;

	if (actual > 0 && TrackNumber > -1) {
		TurnTrackType	const * track;  // Track control pointer.
		TrackType		const	* ptr;  // Pointer to coord offset values.
		int				tracknum;       // The track number being processed.

		track = &TrackControl[TrackNumber];
		if (IsOnShortTrack) {
			tracknum = track->StartTrack;
		} else {
			tracknum = track->Track;
		}
		ptr = RawTracks[tracknum-1].Track;

		Point2D	offset;
		Dir256	dir;

		int y = ptr[TrackIndex].Offset.Y;
		offset.X = ptr[TrackIndex].Offset.X;
		offset.Y = y;
		if (offset != Point2D(0, 0) || !TrackIndex) {

			Coord oldcoord = LinkedTo->PositionCoord;

			dir = ptr[TrackIndex].Facing;
			Coord movement(Smooth_Turn(offset, dir) - LinkedTo->PositionCoord, 0);
			Coord stepcoord = movement + LinkedTo->PositionCoord;
			CellClass * stepcellptr = &Map[stepcoord];

			Coord partial(0, 0, 0);
			movement = Lerp(partial, movement, SpeedAccum / 7.0); /// 7 == (CELL_LEPTON / ((CELL_PIXEL_W + CELL_PIXEL_H) / 2)) // level-2 1.001: the result replaces movement (as in ship.cpp)
			Coord partialcoord = oldcoord + movement; // level-2 1.001: as above

			CellClass * oldcellptr = &Map[oldcoord];
			CellClass * partialcellptr = &Map[partialcoord];

			Coord coord = LinkedTo->PositionCoord; // level-2 1.001: whole coordinates are taken, Z included (as in ship.cpp)

			if (partialcellptr != stepcellptr && partialcellptr != oldcellptr) {
				if (SpeedAccum > 3) {
					coord = stepcoord; // level-2 1.001: as above
				}
			} else {
				coord = partialcoord; // level-2 1.001: as above
			}

			CellClass * newcellptr = &Map[Coord(coord)]; // level-2 1.001: INFERRED, the cell is looked up through a copy of the chosen coordinate (as ship.cpp; While_Moving 0xa0d20 183 -> 110 hunks, not yet matched)

			if (coord.As_Cell() != LinkedTo->PositionCoord.As_Cell()) {
				LinkedTo->Mark(MARK_UP);
				LinkedTo->PositionCoord = coord;
				if (newcellptr->Height == oldcellptr->Height - BRIDGE_CELL_HEIGHT && newcellptr->IsUnderBridge) {
					LinkedTo->IsOnBridge = true;
				}
				if (!newcellptr->IsUnderBridge && oldcellptr->IsUnderBridge) {
					LinkedTo->IsOnBridge = false;
				}
				LinkedTo->Mark(MARK_DOWN);
			} else {
				bool down = LinkedTo->IsDown;
				LinkedTo->IsDown = false;
				LinkedTo->PositionCoord = coord;
				LinkedTo->IsDown = down;
			}
		}
	}

	return(false);
}
