// redalert2-decomp help snippet, package 1 (RA2 1.001 level-2 reconstruction; NOT verified on RA2 1.006)
// Function    : IsometricTileTypeClass::Preview_Tile
// Symbol      : ?Preview_Tile@IsometricTileTypeClass@@QAEPAGHH@Z (the same in both projects)
// Our address : RA2 1.001 GAME.EXE, RVA 0x12c5f0 (VA 0x0052C5F0); source TU src/m85/src/isotype.cpp
// Your address: RA2 1.006, 0x0052E390 (52 bytes), src/recovered/isotype.cpp; manifests/function_map.csv: non_exact, score 81.25
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
 * Copyright 2026 ra2-decomp contributors
 *
 * Contains material derived from Electronic Arts source code.
 * Modified by OpenTS contributors, 2026.
 * EA's GPLv3 Section 7 additional terms and supplemental warranty
 * disclaimers apply; see LICENSE.md.
 ******************************************************************************/

/// <summary>
/// Fetches the preview colors of a sub-tile at the specified lighting level.
/// The tile artwork is loaded on demand, so this routine is safe to call on a tile type
/// that has been trimmed out of memory.
/// </summary>
/// <param name="tile">The sub-tile index within this tile set.</param>
/// <param name="level">The lighting level to fetch the preview colors for.</param>
/// <returns>Returns with a pointer to the low and high preview colors for that level.</returns>
unsigned short * IsometricTileTypeClass::Preview_Tile(int tile, int level)
{ // level-2: adopted from gibbo101 src/isotype.cpp @719fcc7
	unsigned short * preview;
	if (ImageData != NULL) {
		preview = PreviewTiles[tile];
	} else {
		Load_Tile_Image();
		preview = PreviewTiles[tile];
	}
	return &preview[level * 2];
}
