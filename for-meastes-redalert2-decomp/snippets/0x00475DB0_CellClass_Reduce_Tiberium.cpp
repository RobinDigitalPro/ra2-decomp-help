// redalert2-decomp help snippet, package 1 (RA2 1.001 level-2 reconstruction; NOT verified on RA2 1.006)
// Function    : CellClass::Reduce_Tiberium
// Symbol      : ?Reduce_Tiberium@CellClass@@QAEHH@Z (the same in both projects)
// Our address : RA2 1.001 GAME.EXE, RVA 0x759b0 (VA 0x004759B0); source TU src/m85/src/cell.cpp
// Your address: RA2 1.006, 0x00475DB0 (556 bytes), src/recovered/cell.cpp; manifests/function_map.csv: non_exact, score 76.24
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
 * CellClass::Reduce_Tiberium -- Reduces the tiberium in the cell by the amount specified.     *
 *                                                                                             *
 *    This routine will lower the tiberium level in the cell. It is used by the harvesting     *
 *    process as well as by combat damage to the tiberium fields.                              *
 *                                                                                             *
 * INPUT:   levels   -- The number of levels to reduce the tiberium.                           *
 *                                                                                             *
 * OUTPUT:  bool; Was the tiberium level reduced by at least one level?                        *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/19/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
int CellClass::Reduce_Tiberium(int levels)
{
	int reducer = 0; // level-2 1.001: the amount removed is a local set in both branches and returned once; the neighbour cell is the plain Adjacent_Cell result (forms adopted from gibbo101/ra2-decomp src/cell.cpp @721d81e44f, GPL-3.0-or-later; YR 0x00480A80)
	Rect dirty = Union(Overlay_Render_Rect(), Overlay_Shadow_Render_Rect());
	dirty.Y -= TacticalRect.Y;

	TiberiumType tibtype = Tiberium_Type_Here();

	if (levels > 0 && tibtype != TIBERIUM_NONE) {
		TiberiumClass * tiberium = Tiberiums[tibtype];
		if (OverlayData == OVERLAYDATA_TIBERIUM_MAX) {
			tiberium->Queue_Growth(CellID);
		}
		if (OverlayData+1 > levels) {
			OverlayData -= levels;
			reducer = levels;
		} else {
			reducer = OverlayData;
			Overlay = OVERLAY_NONE;
			OverlayData = 0;
			Recalc_Attributes(); // RA2: no passability comparison and no zone update afterwards
			Map.Flag_Background_Update(CellID);
			tiberium->Clear_Spread_State(CellID);
			for (int facing = FACING_FIRST; facing < FACING_COUNT; facing++) {
				Cell adjacent = ::Adjacent_Cell(CellID, (FacingType)facing);
				if (Map.In_Radar(adjacent) && !tiberium->SpreadState[Map_Cell_Index(adjacent)]) {
					tiberium->Queue_Spread(adjacent);
				}
			}
		}
		TacticalMap->Register_Dirty_Area(dirty);
	}
	return(reducer);
}
