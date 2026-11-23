// redalert2-decomp help snippet, package 1 (RA2 1.001 level-2 reconstruction; NOT verified on RA2 1.006)
// Function    : MapGeneratorClass::MapGeneratorClass(void)
// Symbol      : ??0MapGeneratorClass@@QAE@XZ (the same in both projects)
// Our address : RA2 1.001 GAME.EXE, RVA 0x173e00 (VA 0x00573E00); source TU src/m85/src/mapgen.cpp
// Your address: RA2 1.006, 0x00577010 (404 bytes), src/recovered/mapgen.cpp; manifests/function_map.csv: non_exact, score 86.79
// Evidence    : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
//               (compared after masking relocation operands).
// Caution     : 1.001 and 1.006 may differ in this body. Comments of the form "RA2: 0x..." name
//               1.006 addresses; "level-2 1.001:" comments describe what the 1.001 bytes needed.
// License     : GPL-3.0-or-later. Credits carried by this code:
//               - Electronic Arts (GPL source releases; section 7 additional terms)
//               - OpenTS contributors and mischa85/RedAlert2 (the RA2 1.006 tree our source started from)
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

/// <summary>
/// Constructs the random map generator.
/// The game keeps a single generator for its whole run; this routine merely puts it into the
/// idle state it must be in before the first map is asked of it.
/// </summary>
MapGeneratorClass::MapGeneratorClass(void) :
	SeedData(),
	MapSeeder(NULL),
	MapPreview(NULL),
	LocalWidth(0),
	LocalHeight(0),
	RMGMinimumTiberium(2500), // RA2: MapGeneratorClass at 0x577010 matches only so
	RMGMaximumTiberium(5500), // RA2: as above
	MaxTrees(500), // RA2: as above
	PreviewStale(true), // RA2: as above
	SeededWaterAmount(0),
	CellHeight(4), // RA2: as above
	PlaceWaterfall(false) // RA2: as above
{
}

// ---- helper: data members of MapGeneratorClass in declaration order (src/m85/include/mapgen.h); the "RA2: +0x" offsets in comments are layout notes inherited from the 1.006 tree ----
	public:
		/*
		 * These are the settings the next map is to be built from, as the random map dialog
		 * left them. Every generation pass reads the map it is meant to make from here.
		 */
		MapSeedClass SeedData;

		/*
		 * Pointer to a copy of the settings the last preview was built from, kept so that the
		 * generator can tell whether the theater and tile set still suit the map being asked
		 * for or must be loaded afresh.
		 */
		MapSeedClass * MapSeeder;

		/*
		 * Pointer to the thumbnail of the generated map, which the random map dialog shows the
		 * player and the multiplayer code passes on to the other players.
		 */
		MapPreviewClass * MapPreview;

		/*
		 * These are the dimensions of the playable part of the map in cells, chosen from the
		 * seed's size settings and player count. The generator sizes its working arrays and
		 * its region limits from them.
		 */
		int LocalWidth;
		int LocalHeight;

		/*
		**	RA2: random map generator settings.
		*/
		TypeList<int> RMGLevelLightSettings; // RA2: +0x188
		TypeList<int> TemperateAmbientLight;
		TypeList<int> SnowAmbientLight;
		TypeList<int> TemperateAmbientRed;
		TypeList<int> TemperateAmbientGreen;
		TypeList<int> TemperateAmbientBlue;
		TypeList<int> SnowAmbientRed;
		TypeList<int> SnowAmbientGreen;
		TypeList<int> SnowAmbientBlue;
		TypeList<int> RMGVegetationMinimums;
		TypeList<int> RMGVegetationMaximums;
		int RMGMinimumTiberium; // RA2: +0x2BC
		int RMGMaximumTiberium;
		TypeList<BuildingTypeClass const *> TemperateOrePatchLamps; // RA2: +0x2C4
		TypeList<BuildingTypeClass const *> SnowOrePatchLamps;
		int MaxTrees; // RA2: +0x2FC
		bool PreviewStale;

		/*
		 * This is how much water the lake and river passes have laid down so far, measured in
		 * cells. It is what they spend against the seed's water budget.
		 */
		int SeededWaterAmount;

		/*
		 * This is the number given to the region being laid down at the moment. Each water or
		 * ice feature takes the next one, so that a feature which comes out badly can be
		 * wiped again by its number alone.
		 */
		int WorkingRegionID;

		/*
		 * This is the level the whole map is laid out flat at before any hills are raised, and
		 * the level a wiped region is flattened back to.
		 */
		int CellHeight;

		/*
		 * If the rivers of this map may end in a waterfall, then this flag will be true. It is
		 * rolled once per map, so a map either has them or it does not.
		 */
		bool PlaceWaterfall;
};
