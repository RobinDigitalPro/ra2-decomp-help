// ra2-decomp help snippet, update 2026-11-23 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00514310 (2321 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0xfb4c0 (VA 0x004FB4C0, 2229 bytes without padding)
// RA2 symbol : ?Process@HoverLocomotionClass@@UAGEXZ
// similarity : 0.9043 (similar, masked instruction tokens; shape 0.9851)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/hover.cpp
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

/// <returns>bool; Is the object still moving?</returns>
boolean STDMETHODCALLTYPE HoverLocomotionClass::Process(void)
{
	if (Is_Moving() && Is_Moving1()) {
		Motion_AI();
		if (!LinkedTo->IsActive) return(false); // RA2: an inactive unit does not move

		int height = LinkedTo->Height;
		int speed = LinkedTo->Current_Speed() * Acceleration;
		DirType direction = LinkedTo->Direction(HeadToCoord); // level-2 1.001: ObjectClass::Direction(Coord const &) member (hdrlab 2026-11-21) // RA2: through DirType's Direction

		if (speed == 0 && Facing.Current().Is_Complete_Turn(direction, 0)) {
			Start();
			speed = LinkedTo->Current_Speed() * Acceleration;
		}

		if (speed >= Flat_Distance(LinkedTo->PositionCoord, Point2D(HeadToCoord))) {
			LinkedTo->IsOccupyingCell = true;
			LinkedTo->IsToPathAroundBlockage = false;
			WasPushed = false;

			Start_Of_Move(0);

			if (LinkedTo->Path[0] == FACING_NONE && DestinationCoord == COORD_NONE) {
				HeadToCoord = COORD_NONE;
			}

			TechnoClass * contact = LinkedTo->Radio_Link(0); // RA2: the radio contact // level-2 1.001: fetched before the dock cell is set (call precedes the CELL_NONE load)
			Cell dock = CELL_NONE; // RA2: a unit that has reached its docking cell carries on moving
			if (contact != NULL) { // RA2: if there is one
				dock = contact->Destination_Coord(LinkedTo).As_Cell(); // RA2: gives the docking cell // level-2 1.001: vtable +0x4c (Destination_Coord with the unit as docker), not Docking_Coord
			}
			bool at_dock = (LinkedTo->Get_Cell() == dock); // RA2: has the unit reached it

			MoveType ok = MOVE_OK; // level-2 1.001: declared before the block; the result tests follow the block (ok stays in ebx across Per_Cell_Process and is re-tested)
			if (DestinationCoord != COORD_NONE || at_dock) { // RA2: keeps moving at its dock
				ok = While_Moving(true);
				if (!LinkedTo->IsActive || LinkedTo->IsInLimbo || LinkedTo->IsFalling) return(MOVE_NO);
				if (ok == MOVE_OK && HeadToCoord == COORD_NONE) {
					/*
					**	Perform "per cell" activities.
					*/
					LinkedTo->Per_Cell_Process(PCP_END);
					if (!LinkedTo->IsActive || LinkedTo->IsInLimbo || LinkedTo->IsFalling) return(false); // RA2: no NULL test of LinkedTo
				}
			}
			if (ok == MOVE_NO) {
				if (LinkedTo->CurrentTube >= TUBE_FIRST) return(false);
				Stop();
			} else if (ok != MOVE_OK) {
				Stop_Driver();
				speed = 0;
			}
		}

		if (speed > 0) {
			Coord coord = LinkedTo->PositionCoord;

			if (LinkedTo->Occupies_Cells() && HeadToCoord != COORD_NONE) {
				LinkedTo->Clear_Occupy_Bit(LinkedTo->PositionCoord);
				LinkedTo->IsOccupyingCell = false;
				LinkedTo->IsToPathAroundBlockage = false;
			}

			Point2D moved = Move_Point(coord, Facing.Current(), speed); // level-2 1.001: a flat move of an X/Y copy of coord (copied before Facing.Current); Z is not read or written
			coord.X = moved.X;
			coord.Y = moved.Y;
			if (coord.As_Cell() != LinkedTo->Get_Coord().As_Cell()) {
				LinkedTo->Mark(MARK_UP);
				LinkedTo->PositionCoord = coord;
				LinkedTo->Height = height;
				CellClass * cellptr = &Map[coord];
				if (!LinkedTo->IsOnBridge && cellptr->IsUnderBridge && LinkedTo->HeightAGL >= BRIDGE_LEPTON_HEIGHT) {
					LinkedTo->IsOnBridge = true;
				}
				if (LinkedTo->IsOnBridge == true && !cellptr->IsUnderBridge) {
					LinkedTo->IsOnBridge = false;
				}
				LinkedTo->Mark(MARK_DOWN);
			} else {
				bool wasdown = LinkedTo->IsDown;
				LinkedTo->IsDown = false;
				LinkedTo->PositionCoord = coord;
				LinkedTo->Height = height;
				LinkedTo->IsDown = wasdown;
			}
		}
	}

	if (Is_Moving_Now() && (Frame % 10) == 0) {
		if (!LinkedTo->IsOnBridge && LinkedTo->Get_Cell_Ptr()->Land_Type() == LAND_WATER) {
			if (Rule->Wake != NULL) {
				new AnimClass(Rule->Wake, LinkedTo->Get_Coord());
			}
		}
	}

	Gravity_AI();

	if (WasShoved) {
		if (Is_Powered()) {
			DirType dir = LinkedTo->PrimaryFacing.Current();
			LinkedTo->PrimaryFacing.Set(dir + Dir256(ShoveAccum));
			int delta = min(abs(ShoveAccum), 1); // level-2 1.001: always.h min (one inline unit; same code as the flattened test)
			if (ShoveAccum < 0) {
				ShoveAccum += delta;
			} else {
				ShoveAccum -= delta;
			}
			if (ShoveAccum == 0) {
				WasShoved = false;
			}
		} else {
			WasShoved = false;
		}
		if (!WasShoved) {
			Map[LinkedTo->Get_Coord()].Trigger_Veins();
			if (Map[LinkedTo->Get_Coord()].Land_Type() == LAND_WATER) {
				if (LinkedTo->Get_Coord().Z < Map.Get_Height_GL(LinkedTo->Get_Coord()) + LEVEL_LEPTON_H) {
					LinkedTo->Fall_From_Height();
				}
			}
		}
	}

	return(Is_Moving());
}
