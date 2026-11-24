// ra2-decomp help snippet, update 2026-11-23 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006A05F0 (5768 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0x26c8e0 (VA 0x0066C8E0, 5720 bytes without padding)
// RA2 symbol : ?While_Moving@ShipLocomotionClass@@AAE_N_N@Z
// similarity : 0.9008 (similar, masked instruction tokens; shape 0.9830)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/ship.cpp
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

/// <summary>
/// Processes the ship's movement along its track.
/// The speed the ship may build up is accumulated, and every full step of it moves the ship
/// along the track, entering the next cell, crushing what lies in the way and jumping to the
/// following track where the path turns. The part of a step left over is spent on the way.
/// </summary>
/// <param name="just_started">Is this the first call after the move was started?</param>
/// <returns>bool; Is the ship done moving for this frame (arrived or blocked)?</returns>
bool ShipLocomotionClass::While_Moving(bool just_started) // RA2: as above
{
	assert(LinkedTo->IsActive); // RA2: as above

	/*
	**	Perform quick legality checks.
	*/
	if ((!IsDriving || TrackNumber == -1) && LinkedTo->Path[0] != FACING_COUNT || (IsRotating && !LinkedTo->TClass->IsTurretEquipped)) { // RA2: as above
		SpeedAccum = 0;		// Kludge?  No speed should accumulate if movement is on hold. // RA2: as above
		return(false); // RA2: as above
	}
	if (LinkedTo->TClass->IsAccelerates) { // RA2: as above
		bool not_passive = LinkedTo->RTTI != RTTI_UNIT || !((UnitClass *)LinkedTo)->Class->IsPassive; // RA2: as above
		if (TrackNumber < BACKUP_INTO_REFINERY && not_passive) { // RA2: as above
			Coord dest_coord = DestinationCoord; // RA2: as above
			dest_coord.Z = Map.Get_Height_GL(dest_coord) + (Map[dest_coord].IsUnderBridge ? BRIDGE_LEPTON_HEIGHT : 0); // RA2: as above
			int distance = (LinkedTo->PositionCoord - dest_coord).Length();//LinkedTo->PositionCoord.Distance_To(dest_coord); // RA2: as above

			bool forced_speed = false; // RA2: as above
			double speed = LinkedTo->Speed; // RA2: as above

			TechnoTypeClass const * tclass = LinkedTo->TClass; // RA2: as above

			if (distance < tclass->SlowdownDistance) { // RA2: as above
				forced_speed = true; // RA2: as above
				speed = MAX(_ship_deaccel, speed - tclass->MaxSpeed * tclass->DeaccelerationFactor); // RA2: the type's MaxSpeed, not Get_Max_Speed()
			} else if (LinkedTo->IsSinking) { // RA2: as above
				speed = MAX(_ship_sinking, speed - tclass->MaxSpeed * _ship_sinking_scale); // RA2: as above
				forced_speed = true; // RA2: as above
			}

			if (LinkedTo->IsCrushing) { // RA2: as above
				TargetSpeed = MIN(TargetSpeed, 0.2); // RA2: as above
				LinkedTo->Set_Speed(TargetSpeed); // RA2: as above
			} else if (forced_speed) { // RA2: as above
				LinkedTo->Set_Speed(speed); // RA2: as above
			} else if (LinkedTo->Speed < TargetSpeed) { // RA2: as above
				LinkedTo->Set_Speed(MIN(TargetSpeed, LinkedTo->Speed + tclass->AccelerationFactor)); // RA2: as above
			} else if (LinkedTo->Speed > TargetSpeed) { // RA2: as above
				LinkedTo->Set_Speed(MAX(TargetSpeed, LinkedTo->Speed - tclass->MaxSpeed * tclass->DeaccelerationFactor)); // RA2: as above
			}

			if (LinkedTo->RTTI == RTTI_UNIT) { // RA2: as above
				UnitClass * following = ((UnitClass *)LinkedTo)->FollowingMe; // RA2: as above
				if (following != NULL) { // RA2: as above
					do { // RA2: as above
						following->Set_Speed(LinkedTo->Speed); // RA2: as above
						following = following->FollowingMe; // RA2: as above
					} while (following && following != following->FollowingMe); // RA2: as above
				}
			}
		}
	} else {
		LinkedTo->Set_Speed(TargetSpeed); // RA2: as above
	}

	/*
	**	If enough movement has accumulated so that the unit can
	**	visibly move on the map, then process accordingly.
	**	Slow the unit down if he's carrying a flag.
	*/
	int maxspeed = LinkedTo->Current_Speed(); // RA2: as above
	//if (IsFormationMove) maxspeed = FormationMaxSpeed;

	int actual;			// Working movement addition value. // RA2: as above
	actual = SpeedAccum + (just_started ? 0 : maxspeed); // RA2: the speed accumulation comes before the next facing is read

	FacingType		nextface;		// Next facing queued in path. // RA2: declared after actual
	nextface = LinkedTo->Path[0]; // RA2: as above

	if (nextface == FACING_COUNT && TrackNumber == -1) { // RA2: as above
		LinkedTo->Mark(MARK_UP); // RA2: as above
		Stop_Driver(); // RA2: as above

		TubeType tubenum = (TubeType)LinkedTo->Get_Cell_Ptr()->Tube; // RA2: as above
		if (tubenum >= TUBE_FIRST && tubenum < Tubes.Count()) { // RA2: as above
			TubeClass * tube = Tubes[tubenum]; // RA2: as above
			Cell c = tube->Exit; // RA2: as above
			HeadToCoord = c.As_Coord(); // RA2: as above
			memcpy((char*)&LinkedTo->Path, (char*)&LinkedTo->Path[1], sizeof(LinkedTo->Path[0]) * (CONQUER_PATH_MAX-1)); // RA2: as above
			LinkedTo->Path[CONQUER_PATH_MAX-1] = FACING_NONE; // RA2: as above
			LinkedTo->CurrentTube = tubenum; // RA2: as above
			TPoint2D<short> const & enter = tube->Enter; // RA2: the entry point is held in a reference before the tube direction is set
			LinkedTo->CurrentTubeDir = FACING_FIRST; // RA2: as above
			LinkedTo->LastTubeCoord = Map[Adjacent_Cell(Cell(enter), tube->Dirs[0])].Cell_Coord(); // RA2: as above
			int current_height = Map.Get_Height_GL(LinkedTo->PositionCoord); // RA2: as above
			Cell exit = tube->Exit; // RA2: the exit cell is a new local, read before the count
			int count = tube->Count; // RA2: as above
			LinkedTo->LastTubeCoord.Z = current_height + (Map.Get_Height_GL(exit) - current_height) / count; // RA2: uses the new local
			IsDriving = true; // RA2: as above
			TrackNumber = -1; // RA2: as above
		} else {
			LinkedTo->Path[0] = FACING_NONE; // RA2: as above
			TrackNumber = -1; // RA2: as above
			HeadToCoord = COORD_NONE; // RA2: as above
			Stop_Driver(); // RA2: as above
		}
		return(false); // RA2: as above
	}

	if (actual > ((PIXEL_LEPTON_W + PIXEL_LEPTON_H) / 2)) { // RA2: as above
		TurnTrackType	const * track;  // Track control pointer. // RA2: as above
		TrackType		const	* ptr;  // Pointer to coord offset values. // RA2: as above
		int				tracknum;       // The track number being processed. // RA2: as above
		bool				adj;        // Is a turn coming up? // RA2: as above

		track = &TrackControl[TrackNumber]; // RA2: as above
		if (IsOnShortTrack) { // RA2: as above
			tracknum = track->StartTrack; // RA2: as above
		} else {
			tracknum = track->Track; // RA2: as above
		}
		ptr = RawTracks[tracknum-1].Track; // RA2: as above
		//nextface = LinkedTo->Path[0];

		if (nextface < FACING_NONE || nextface > FACING_COUNT) { // RA2: as above
			LinkedTo->Path[0] = FACING_NONE; // RA2: as above
			return(false); // RA2: as above
		}

		/*
		**	Determine if there is a turn coming up. If there is
		**	a turn, then track jumping might occur.
		*/
		adj = false; // RA2: as above
		if (nextface != FACING_COUNT && nextface != FACING_NONE && Dir_Facing(track->Facing) != nextface) { // RA2: as above
			adj = true; // RA2: as above
		}

		/*
		**	Skip ahead the number of track steps required (limited only
		**	by track length). Set the unit to the new position and
		**	flag the unit accordingly.
		*/
		//LinkedTo->Mark(MARK_UP);
		while (actual > (PIXEL_LEPTON_W + PIXEL_LEPTON_H) / 2) { // RA2: as above
			Point2D	offset; // RA2: as above
			Dir256	dir; // RA2: as above

			actual -= (PIXEL_LEPTON_W + PIXEL_LEPTON_H) / 2; // RA2: as above

			offset = ptr[TrackIndex].Offset; // RA2: as above
			if (offset != Point2D(0, 0) || !TrackIndex) { // RA2: as above
				if (LinkedTo->Occupies_Cells()) { // RA2: as above
					LinkedTo->Clear_Occupy_Bit(LinkedTo->PositionCoord); // RA2: as above
					LinkedTo->IsOccupyingCell = false; // RA2: as above
					LinkedTo->IsToPathAroundBlockage = false; // RA2: as above
				}

				Cell oldcell; // RA2: as above
				if (!TrackIndex) { // RA2: as above
					oldcell = LinkedTo->PositionCell; // RA2: as above
				} else {
					dir = ptr[TrackIndex - 1].Facing; // RA2: as above
					Point2D prevoffset = ptr[TrackIndex - 1].Offset; // RA2: as above
					oldcell = Coord(Smooth_Turn(prevoffset, dir), 0).As_Cell(); // RA2: as above
				}

				dir = ptr[TrackIndex].Facing; // RA2: as above
				Coord newcoord = Coord(Smooth_Turn(offset, dir), 0); // RA2: as above
				Cell newcoord_cell = newcoord.As_Cell(); // RA2: both cells are read into locals before the comparison
				Cell linked_coord_cell = LinkedTo->PositionCoord.As_Cell(); // RA2: as above
				Cell newcell = newcoord.As_Cell(); // RA2: as above

				if (newcoord_cell != linked_coord_cell) { // RA2: as above
					LinkedTo->Mark(MARK_UP); // RA2: as above
					LinkedTo->PositionCoord = newcoord; // RA2: as above
					CellClass * oldcellptr = &Map[oldcell]; // RA2: as above
					CellClass * newcellptr = &Map[newcell]; // RA2: as above
					if (newcellptr->Height == oldcellptr->Height - BRIDGE_CELL_HEIGHT && newcellptr->IsUnderBridge) { // RA2: as above
						LinkedTo->IsOnBridge = true; // RA2: as above
					}
					if (!newcellptr->IsUnderBridge && oldcellptr->IsUnderBridge) { // RA2: as above
						LinkedTo->IsOnBridge = false; // RA2: as above
					}
					UnitClass * train; // level-2 1.001: the unit is held in a local across the crush loop
					if (LinkedTo->TClass->IsTrain && !(train = (UnitClass *)LinkedTo)->IsFollowing) { // level-2 1.001: as above
						bool on_bridge = train->IsOnBridge ||
							LinkedTo->PositionCoord.Z >= Map.Get_Height_GL(LinkedTo->PositionCoord) + BRIDGE_LEPTON_HEIGHT;
						ObjectClass * occupier = on_bridge
							? Map[newcell].Cell_Bridge_Occupier()
							: Map[newcell].Cell_Occupier(false);
						while (occupier != NULL) { // RA2: as above
							ObjectClass * next = occupier->Next; // RA2: as above
							if (!occupier->Class_Of()->IsCrushable) { // RA2: as above
								int strength = 10000; // RA2: as above
								occupier->Take_Damage(strength, 0, Rule->C4Warhead, NULL, true, true); // RA2: as above
								strength = 20; // RA2: as above
								train->Take_Damage(strength, 0, Rule->C4Warhead, NULL, true, false); // level-2 1.001: as above
							}
							occupier = next; // RA2: as above
						}
					}
					if (!LinkedTo->IsActive) return(false); // RA2: as above
					LinkedTo->Mark(MARK_DOWN); // RA2: as above

					if (newcellptr->Overlay != OVERLAY_NONE) { // RA2: as above
						OverlayTypeClass * otype = OverlayTypes[newcellptr->Overlay]; // RA2: as above
						if (IsRocking && (LinkedTo->TClass->IsCrusher || LinkedTo->Has_Ability(ABILITY_CRUSHER)) && otype->HeapID == OVERLAY_SANDBAG_WALL) { // RA2: as above
							LinkedTo->IsCrushing = true; // RA2: as above
							if (LinkedTo->TClass->IsTiltsWhenCrushes) { // RA2: as above
								LinkedTo->RockingForwardsPerFrame = -0.02f; // RA2: as above
							}
						}
					}
				} else {
					bool down = LinkedTo->IsDown; // RA2: as above
					LinkedTo->IsDown = false; // RA2: as above
					LinkedTo->PositionCoord = newcoord; // RA2: as above
					LinkedTo->IsDown = down; // RA2: as above
				}

				if (!LinkedTo->IsActive) { // RA2: as above
					return(false); // RA2: as above
				}

				bool down = LinkedTo->IsDown; // RA2: as above
				LinkedTo->IsDown = false; // RA2: as above
				LinkedTo->HeightAGL = 0; // RA2: as above
				LinkedTo->IsDown = down; // RA2: as above

				LinkedTo->PrimaryFacing.Set(dir); // RA2: as above

				/*
				**	See if "per cell" processing is necessary.
				*/
				if (TrackIndex && RawTracks[tracknum-1].Cell == TrackIndex) { // RA2: as above
					LinkedTo->Clear_Occupy_Bit(LinkedTo->PositionCoord); // RA2: as above
				}

				/*
				**	The unit could "jump tracks". Check to see if the unit should
				**	do so.
				*/
				if (nextface != FACING_COUNT && nextface != FACING_NONE && adj && RawTracks[tracknum-1].Jump == TrackIndex && TrackIndex) { // RA2: as above
					TurnTrackType const * newtrack;		// Proposed jump-to track. // RA2: as above
					int	tnum; // RA2: as above

					tnum = DirType(track->Facing).As_Dir8() * FACING_COUNT + nextface; // RA2: as above
					newtrack = &TrackControl[tnum]; // RA2: as above
					if (newtrack->Track && RawTracks[newtrack->Track-1].Entry) { // RA2: as above
						double oldspeed = LinkedTo->Speed; // RA2: as above

						Coord c = Adjacent_Cell(HeadToCoord, nextface); // RA2: as above

						switch (LinkedTo->Can_Enter_Cell(&Map[c.As_Cell()], nextface, LinkedTo->Get_Cell_Height())) { // RA2: as above
							case MOVE_OK: // RA2: as above
							case MOVE_MOVING_BLOCK: // RA2: as above
								if (LinkedTo->RTTI == RTTI_UNIT && !((UnitClass *)LinkedTo)->Class->IsPassive) break; // RA2: as above
								IsOnShortTrack = false;		// Shouldn't be necessary, but... // RA2: as above
								TrackNumber = tnum; // RA2: as above
								track = newtrack; // RA2: as above

								tracknum = track->Track; // RA2: as above
								TrackIndex = RawTracks[tracknum-1].Entry-1;	// Anticipate increment. // RA2: as above
								ptr = RawTracks[tracknum-1].Track; // RA2: as above
								adj = false; // RA2: as above

								Stop_Driver(); // RA2: as above
								IsDriving = true; // RA2: as above
								LinkedTo->Per_Cell_Process(PCP_END); // RA2: as above
								IsDriving = false; // RA2: as above
								if (!LinkedTo->IsActive || LinkedTo->IsInLimbo || LinkedTo->IsFalling) return(false); // level-2 1.001: no LinkedTo == NULL test
								if (Start_Driver(c)) { // RA2: as above
									LinkedTo->Set_Speed(oldspeed); // RA2: as above
									memcpy((char*)&LinkedTo->Path, (char*)&LinkedTo->Path[1], sizeof(LinkedTo->Path[0]) * (CONQUER_PATH_MAX-1)); // RA2: as above
									LinkedTo->Path[CONQUER_PATH_MAX-1] = FACING_NONE; // RA2: as above
								}
								break; // RA2: as above

							case MOVE_CLOAK: // RA2: as above
								Map[c].Shimmer(); // RA2: as above
								break; // RA2: as above

							case MOVE_CLOSED_GATE: // RA2: as above
								{
									Cell gate = c.As_Cell();
									Map.Try_Open_Gate(LinkedTo, gate);
								} // RA2: as above
								break; // RA2: as above

							case MOVE_TEMP: { // RA2: as above
									bool bridge; // RA2: as above
									if (!Map[c].IsUnderBridge || abs(LinkedTo->PositionCoord.Z / LEVEL_LEPTON_H - Map[c].Height) <= 2) { // RA2: as above
										bridge = false; // RA2: as above
									} else {
										bridge = true; // RA2: as above
									}
									Map[HeadToCoord].Incoming(COORD_NONE, true, true, bridge); // RA2: as above
								}
								break; // RA2: as above
						}
					}
				}
				TrackIndex++; // RA2: as above

			} else {
				Coord dc = HeadToCoord - LinkedTo->PositionCoord; // RA2: as above
				int d = abs(dc.X) + abs(dc.Y); // RA2: as above
				actual += (int)((1.0 - (double)d / 11.0) * 7.0); // RA2: as above
				LinkedTo->IsOccupyingCell = true; // RA2: as above
				LinkedTo->IsToPathAroundBlockage = false; // RA2: as above

				Cell poscell = LinkedTo->PositionCoord.As_Cell(); // level-2 1.001: the unit's cell is read first and is the left operand (1.001 compares position against head-to)
				if (poscell != HeadToCoord.As_Cell()) { // level-2 1.001: as above
					LinkedTo->Mark(MARK_UP); // RA2: as above
					LinkedTo->PositionCoord = HeadToCoord; // RA2: as above
					LinkedTo->HeightAGL = 0; // RA2: as above
					LinkedTo->Mark(MARK_DOWN); // RA2: as above
				} else {
					bool down = LinkedTo->IsDown; // RA2: as above
					LinkedTo->IsDown = false; // RA2: as above
					LinkedTo->PositionCoord = HeadToCoord; // RA2: as above
					LinkedTo->HeightAGL = 0; // RA2: as above
					LinkedTo->IsDown = down; // RA2: as above
				}

				//actual = 0;
				//DestinationCoord = Head_To_Coord();
				Stop_Driver(); // RA2: as above
				TrackNumber = -1; // RA2: as above
				TrackIndex = NULL; // RA2: as above

				bool arrived = false; // RA2: as above
				if (LinkedTo->NavCom != NULL && LinkedTo->PositionCell == LinkedTo->NavCom->Destination_Coord(LinkedTo).As_Cell()) { // level-2 1.001: the unit is passed as the docker (1.001 pushes LinkedTo, not NULL)
					if (abs(LinkedTo->Destination_Coord(LinkedTo).Z - DestinationCoord.Z) < 2 * LEVEL_LEPTON_H) { // level-2 1.001: as above
						arrived = true; // RA2: as above
						DestinationCoord = COORD_NONE; // RA2: as above
						Stop_Driver(); // RA2: as above
						IsDriving = false; // RA2: as above
					}
				}

				/*
				**	Perform "per cell" activities.
				*/
				//LinkedTo->Mark(MARK_DOWN);
				LinkedTo->Per_Cell_Process(PCP_END); // RA2: as above
				if (!LinkedTo->IsActive || LinkedTo->IsInLimbo || LinkedTo->IsFalling) return(true); // level-2 1.001: no LinkedTo == NULL test
				//LinkedTo->Mark(MARK_UP);

				if (arrived) { // RA2: as above
					LinkedTo->Abort_Motion(); // RA2: not just NavCom = NULL
					LinkedTo->Path[0] = FACING_NONE; // RA2: as above
					if (LinkedTo->Mission == MISSION_MOVE && LinkedTo->Enter_Idle_Mode()) { // RA2: as above
						return(true); // RA2: as above
					}
				}

				if (LinkedTo->Is_Docked_For_Repair()) { // RA2: as above
					return(true); // RA2: as above
				}

				if (!LinkedTo->IsActive) return(false); // RA2: as above

				break; // RA2: as above
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
	SpeedAccum = actual; // RA2: as above

	if (actual > 0 && TrackNumber > -1) { // RA2: as above
		TurnTrackType	const * track;  // Track control pointer. // RA2: as above
		TrackType		const	* ptr;  // Pointer to coord offset values. // RA2: as above
		int				tracknum;       // The track number being processed. // RA2: as above

		track = &TrackControl[TrackNumber]; // RA2: as above
		if (IsOnShortTrack) { // RA2: as above
			tracknum = track->StartTrack; // RA2: as above
		} else {
			tracknum = track->Track; // RA2: as above
		}
		ptr = RawTracks[tracknum-1].Track; // RA2: as above

		Point2D	offset; // RA2: as above
		Dir256	dir; // RA2: as above

		int y = ptr[TrackIndex].Offset.Y;
		offset.X = ptr[TrackIndex].Offset.X;
		offset.Y = y; // RA2: as above
		if (offset != Point2D(0, 0) || !TrackIndex) { // RA2: as above

			Coord oldcoord = LinkedTo->PositionCoord; // RA2: as above

			dir = ptr[TrackIndex].Facing; // RA2: as above
			Coord movement(Smooth_Turn(offset, dir) - LinkedTo->PositionCoord, 0); // level-2 1.001: constructed in place (no copy of a temporary; the 1.001 registers of this block follow)
			Coord stepcoord = movement + LinkedTo->PositionCoord; // RA2: as above
			CellClass * stepcellptr = &Map[stepcoord]; // RA2: as above

			Coord partial(0, 0, 0); // RA2: as above
			movement = Lerp(partial, movement, SpeedAccum / 7.0); // RA2: the blended step overwrites the movement /// 7 == (CELL_LEPTON / ((CELL_PIXEL_W + CELL_PIXEL_H) / 2))
			Coord partialcoord = oldcoord + movement; // RA2: as above

			CellClass * oldcellptr = &Map[oldcoord]; // RA2: as above
			CellClass * partialcellptr = &Map[partialcoord]; // RA2: as above

			Coord coord = LinkedTo->PositionCoord; // RA2: the height is not kept apart: the chosen coordinate replaces it whole

			if (partialcellptr != stepcellptr && partialcellptr != oldcellptr) { // RA2: as above
				if (SpeedAccum > 3) { // RA2: as above
					coord = stepcoord; // RA2: as above
				}
			} else {
				coord = partialcoord; // RA2: as above
			}

			CellClass * newcellptr = &Map[Coord(coord)]; // level-2 1.001: INFERRED, the cell is looked up through a copy of the chosen coordinate (1.001 copies the coord registers into a temporary for operator[]; While_Moving 0x26c8e0 172 -> 99 hunks, not yet matched)

			if (coord.As_Cell() != LinkedTo->PositionCoord.As_Cell()) { // RA2: as above
				LinkedTo->Mark(MARK_UP); // RA2: as above
				LinkedTo->PositionCoord = coord; // RA2: as above
				if (newcellptr->Height == oldcellptr->Height - BRIDGE_CELL_HEIGHT && newcellptr->IsUnderBridge) { // RA2: as above
					LinkedTo->IsOnBridge = true; // RA2: as above
				}
				if (!newcellptr->IsUnderBridge && oldcellptr->IsUnderBridge) { // RA2: as above
					LinkedTo->IsOnBridge = false; // RA2: as above
				}
				LinkedTo->Mark(MARK_DOWN); // RA2: as above
			} else {
				bool down = LinkedTo->IsDown; // RA2: as above
				LinkedTo->IsDown = false; // RA2: as above
				LinkedTo->PositionCoord = coord; // RA2: as above
				LinkedTo->IsDown = down; // RA2: as above
			}
		}
	}

	return(false); // RA2: as above
}
