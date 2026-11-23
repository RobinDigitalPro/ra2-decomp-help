// redalert2-decomp help snippet, package 1 (RA2 1.001 level-2 reconstruction; NOT verified on RA2 1.006)
// Function    : DisplayClass::Set_Cursor_Pos
// Symbol      : ?Set_Cursor_Pos@DisplayClass@@QAE?AVCell@@ABV2@@Z (the same in both projects)
// Our address : RA2 1.001 GAME.EXE, RVA 0x992b0 (VA 0x004992B0); source TU src/m85/src/display.cpp
// Your address: RA2 1.006, 0x004994D0 (832 bytes), src/recovered/display.cpp; manifests/function_map.csv: non_exact, score 69.2
// Evidence    : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
//               (compared after masking relocation operands).
// Caution     : 1.001 and 1.006 may differ in this body. Comments of the form "RA2: 0x..." name
//               1.006 addresses; "level-2 1.001:" comments describe what the 1.001 bytes needed.
// License     : GPL-3.0-or-later. Credits carried by this code:
//               - Electronic Arts (GPL source releases; section 7 additional terms)
//               - OpenTS contributors and mischa85/RedAlert2 (the RA2 1.006 tree our source started from)
//               - gibbo101/ra2-decomp (forms adopted in this body; see the comments in it)
//               The notice of our source file follows. Please keep notices and credits.
// Use         : a read-only lead with our layouts and names. Port the idea; let your checker decide.

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
 * DisplayClass::Set_Cursor_Pos -- Controls the display and animation of the tac cursor.       *
 *                                                                                             *
 *    This routine controls the location, display, and animation of the                        *
 *    tactical map cursor.                                                                     *
 *                                                                                             *
 * INPUT:   pos   -- Position to move the cursor do. If -1 is passed then                      *
 *                   the cursor will just be hidden. If the position                           *
 *                   passed is the same as the last position passed in,                        *
 *                   then animation could occur (based on timers).                             *
 *                                                                                             *
 * OUTPUT:     none                                                                            *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/22/1991 JLB : Created.                                                                 *
 *   06/02/1994 JLB : Converted to member function.                                            *
 *   06/08/1994 JLB : If position is -1, then follow mouse.                                    *
 *   02/28/1995 JLB : Forces placement cursor to fit on map.                                   *
 *=============================================================================================*/
Cell DisplayClass::Set_Cursor_Pos(Cell const & xpos)
{ // level-2: adopted from gibbo101 src/display.cpp @719fcc7
	Cell result;
	Cell pos = xpos;

	if (pos == CELL_NONE) {
		Point2D const & current = MouseCursor->Get_Mouse_Point();
		Rect bounds = TacticalRect;
		if (bounds.Is_Point_Within(current)) {
			result = Map.Click_Cell_Calc(Get_Mouse_Point());
			if (result != CELL_NONE) {
				pos = result;
			}
		} else {
			pos = TacticalMap->Pixel_To_Cell(Get_Mouse_Point() - bounds.TopLeft);
		}
	}

	if (CursorSize == NULL) {
		result = ZoneCell;
		ZoneCell = pos;
		return(result);
	}

	Cell cursor;
	if (!Debug_Map) {
		cursor = TacticalMap->Clamp_Cursor_To_Tactical(pos + ZoneOffset, CursorSize) - ZoneOffset;
	} else {
		cursor = pos;
	}

	if (cursor == ZoneCell) return(cursor);

	result = ZoneCell;
	if (CursorSize != NULL) {
		if (cursor != ZoneCell && ZoneCell != CELL_NONE) {
			Cursor_Mark(ZoneCell+ZoneOffset, false);
		}
		if (cursor != CELL_NONE) {
			Cursor_Mark(cursor+ZoneOffset, true);
		}
	}
	ZoneCell = cursor;
	ProximityCheck = Passes_Proximity_Check(PendingObject, PendingHouse, CursorSize, ZoneCell+ZoneOffset);
	ShroudCheck = Passes_Shroud_Check(PendingObject, PendingHouse, CursorSize, ZoneCell+ZoneOffset);

	return(result);
}
