// ra2-decomp help snippet, update 2026-11-23 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00598960 (3018 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0x176ec0 (VA 0x00576EC0, 3086 bytes without padding)
// RA2 symbol : ?Generate_Random_Map@MapGeneratorClass@@QAEX_NPAUHWND__@@@Z
// similarity : 0.9606 (very-similar, masked instruction tokens; shape 0.9831)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/mapgen.cpp
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
/// Generates a complete random map.
/// This is the top level of the random map generator. Working from the seed data the player
/// settled on, it lays down the water, carves the terrain into regions, finds somewhere for each
/// player to start, and then dresses the result with veinholes, tiberium, towns, hills and
/// vegetation, reporting its progress as it goes.
/// </summary>
/// <param name="full_init">Should the scenario be rebuilt from scratch and the preview redrawn
/// between phases?</param>
/// <param name="dialog">The map generator dialog to repaint as the preview is refreshed.</param>
void MapGeneratorClass::Generate_Random_Map(bool full_init, HWND dialog) // RA2: RA2's form (0x57A0D0): no ice smoothing, veinholes, lights or urban areas; RMG.INI read here; the preview goes to the guests of a tour game
{
	int index; // RA2: counters shared by the loops below
	CellClass * cptr; // RA2: as above

	if (RMGCallback != NULL) RMGCallback();

	RMGRandom = Random2Class(SeedData.Seed);
	RMGGaussian = NormalDistribution(Random_Fraction);

	if (RMGCallback != NULL) RMGCallback();

	bool show_progress = !Scen->IsReadingScenario; // RA2: kept in a local, the progress screen is closed again at the end
	if (show_progress) { // RA2: the local flag
		Progress.Initialize(100, 1, dialog); // RA2: the dialog window
		Progress.Set_Graphic_Data("PROGBAR2.SHP");
		Progress.Set_Layout(Point2D(-1, -1), NULL, false, true); // RA2: the layout is set apart
		Progress.Display_Progress();
		HWND control = GetDlgItem(dialog, 0x638); // RA2: a control of the dialog, shown while the map is made
		if (control != NULL) { // RA2: as above
			ShowWindow(control, SW_SHOW); // RA2: as above
		}
	}

	if (RMGCallback != NULL) RMGCallback();

	DebugString("RMG: Init random map\n");

	Init_Map(full_init);

	if (RMGCallback != NULL) RMGCallback();

	ScenarioInit++; // RA2: as above

	if (full_init) { // RA2: as above
		RandomMapGen.MapPreview->Create_Preview(); // RA2: as above
		SendMessage(dialog, WM_PAINT, 0, 0); // RA2: as above
		if (Session.Type == GAME_INTERNET && Session.TournamentState == 2) { // RA2: a tour game sends each new preview to the guests
			Send_Map_Preview(RandomMapGen.MapPreview); // RA2: as above
		}
	}

	if (RMGCallback != NULL) RMGCallback();

	Read_RMG_INI(); // RA2: RMG.INI is read here, not in the constructor

	DebugString("RMG: Seeding water\n");

	if (SeedData.MapType == 3 || SeedData.MapType == 4) { // RA2: the inland and mountainous maps keep their water apart from the land
		if (SeedData.WaterAmount != 0) { // RA2: as above
			Seed_Water(); // RA2: as above
		}
	} else {
		Seed_Land(); // RA2: the other maps lay land down first
	}

	Vary_Water_Tiles(); // RA2: 0x57DE10

	Update_Progress(55);

	if (RMGCallback != NULL) RMGCallback();

	if (full_init) { // RA2: as above
		RandomMapGen.MapPreview->Create_Preview(); // RA2: as above
		SendMessage(dialog, WM_PAINT, 0, 0); // RA2: as above
		if (Session.Type == GAME_INTERNET && Session.TournamentState == 2) { // RA2: a tour game sends each new preview to the guests
			Send_Map_Preview(RandomMapGen.MapPreview); // RA2: as above
		}
	}

	if (RMGCallback != NULL) RMGCallback();

	Update_Progress(60); // RA2: no ice smoothing

	if (RMGCallback != NULL) RMGCallback();

	if (full_init) { // RA2: as above
		RandomMapGen.MapPreview->Create_Preview(); // RA2: as above
		SendMessage(dialog, WM_PAINT, 0, 0); // RA2: as above
		if (Session.Type == GAME_INTERNET && Session.TournamentState == 2) { // RA2: a tour game sends each new preview to the guests
			Send_Map_Preview(RandomMapGen.MapPreview); // RA2: as above
		}
	}

	if (RMGCallback != NULL) RMGCallback();

	DebugString("RMG: Init regions\n");

	Init_Regions();

	Update_Progress(65);

	if (RMGCallback != NULL) RMGCallback();

	DebugString("RMG: Making regions\n");

	if (SeedData.MapType == 4 || SeedData.MapType == 3) { // RA2: as above
		MapRegionClass::Make_Ice_Regions(); // RA2: as above
		MapRegionClass::Make_Regions(); // RA2: as above
		Fixup_Cliff_Corners(); // RA2: 0x5831C0
		Map.Build_All_Cliffs(0, -1); // RA2: as above
		Vary_Cliff_Runs(); // RA2: 0x582FD0
	}

	Update_Progress(70);

	if (RMGCallback != NULL) RMGCallback();

	if (full_init) { // RA2: as above
		RandomMapGen.MapPreview->Create_Preview(); // RA2: as above
		SendMessage(dialog, WM_PAINT, 0, 0); // RA2: as above
		if (Session.Type == GAME_INTERNET && Session.TournamentState == 2) { // RA2: a tour game sends each new preview to the guests
			Send_Map_Preview(RandomMapGen.MapPreview); // RA2: as above
		}
	}

	if (RMGCallback != NULL) RMGCallback();

	Scatter_Green_Tiles(); // RA2: 0x57CF20

	DebugString("RMG: Recalculating cell attributes\n");
	Map.Reset_Iterator(); // RA2: as above
	for (cptr = Map.Iterate(); cptr != NULL; cptr = Map.Iterate()) { // RA2: as above
		cptr->Recalc_Attributes(-1); // RA2: as above
	}

	if (RMGCallback != NULL) RMGCallback();

	Update_Progress(75);

	DebugString("RMG: Creating starting points\n");

	bool ok = false;
	while (!ok) {
		ok = Generate_Starting_Points();
		if (ok) {
			ok = Init_Start_Points();
		}
	}

	DebugString("RMG: Adding tech buildings\n"); // RA2: the neutral buildings stand in for the lights and urban areas
	if (SeedData.MapType != 0) { // RA2: as above
		Generate_Neutral_Buildings(); // RA2: 0x58AD90
	}

	if (RMGCallback != NULL) RMGCallback();

	DebugString("RMG: Creating tiberium\n");
	Create_Tiberium();

	if (RMGCallback != NULL) RMGCallback(); // RA2: as above

	if (RMGCellData != NULL) { // RA2: the work cells are reset for the next stage
		int size = MapCellStride * MapCellStride; // RA2: as above
		for (index = 0; index < size; index++) { // RA2: as above
			RMGCellData[index].RegionID = -1; // RA2: as above
			RMGCellData[index].SpreadID = -1; // RA2: as above
		}
	}

	for (index = MapRegionClass::MapRegions.Count() - 1; index >= 0; index--) { // RA2: the regions are dropped here as well as at the end
		MapRegionClass * region = MapRegionClass::MapRegions[index]; // RA2: as above
		if (region != NULL) { // RA2: as above
			delete region; // RA2: as above
		}
	}

	MapRegionClass::TotalCount = 0; // RA2: as above

	DebugString("RMG: Recalculating cell attributes\n");
	Map.Reset_Iterator(); // RA2: as above
	for (cptr = Map.Iterate(); cptr != NULL; cptr = Map.Iterate()) { // RA2: as above
		cptr->Recalc_Attributes(-1); // RA2: as above
	}

	Update_Progress(80);

	if (RMGCallback != NULL) RMGCallback();

	if (full_init) { // RA2: as above
		RandomMapGen.MapPreview->Create_Preview(); // RA2: as above
		SendMessage(dialog, WM_PAINT, 0, 0); // RA2: as above
		if (Session.Type == GAME_INTERNET && Session.TournamentState == 2) { // RA2: a tour game sends each new preview to the guests
			Send_Map_Preview(RandomMapGen.MapPreview); // RA2: as above
		}
	}

	if (RMGCallback != NULL) RMGCallback();

	Update_Progress(85); // RA2: no urban or rural areas

	if (RMGCallback != NULL) RMGCallback();

	if (full_init) { // RA2: as above
		RandomMapGen.MapPreview->Create_Preview(); // RA2: as above
		SendMessage(dialog, WM_PAINT, 0, 0); // RA2: as above
		if (Session.Type == GAME_INTERNET && Session.TournamentState == 2) { // RA2: a tour game sends each new preview to the guests
			Send_Map_Preview(RandomMapGen.MapPreview); // RA2: as above
		}
	}

	if (RMGCallback != NULL) RMGCallback();

	DebugString("RMG: Recalculating cell attributes\n");
	Map.Reset_Iterator(); // RA2: as above
	for (cptr = Map.Iterate(); cptr != NULL; cptr = Map.Iterate()) { // RA2: as above
		cptr->Recalc_Attributes(-1); // RA2: as above
	}

	if (RMGCallback != NULL) RMGCallback();

	DebugString("RMG: Creating hills\n");
	Generate_Hills();

	Update_Progress(90);

	if (RMGCallback != NULL) RMGCallback();

	if (full_init) { // RA2: as above
		RandomMapGen.MapPreview->Create_Preview(); // RA2: as above
		SendMessage(dialog, WM_PAINT, 0, 0); // RA2: as above
		if (Session.Type == GAME_INTERNET && Session.TournamentState == 2) { // RA2: a tour game sends each new preview to the guests
			Send_Map_Preview(RandomMapGen.MapPreview); // RA2: as above
		}
	}

	if (RMGCallback != NULL) RMGCallback();

	DebugString("RMG: Creating LATs, rocks etc\n");

	if (SeedData.Biome == 0) { // RA2: only the temperate biome
		Seed_Vegetation();
		Generate_Vegetation();
	} else {
		Seed_Arctic_Vegetation();
		Generate_Arctic_Vegetation();
	}

	if (RMGCallback != NULL) RMGCallback();

	Update_Progress(95);

	if (RMGCallback != NULL) RMGCallback();

	if (full_init) { // RA2: as above
		RandomMapGen.MapPreview->Create_Preview(); // RA2: as above
		SendMessage(dialog, WM_PAINT, 0, 0); // RA2: as above
		if (Session.Type == GAME_INTERNET && Session.TournamentState == 2) { // RA2: a tour game sends each new preview to the guests
			Send_Map_Preview(RandomMapGen.MapPreview); // RA2: as above
		}
	}

	ScenarioInit--;

	if (RMGCallback != NULL) RMGCallback();

	DebugString("RMG: Recalculating cell attributes\n");
	Map.Reset_Iterator(); // RA2: as above
	for (cptr = Map.Iterate(); cptr != NULL; cptr = Map.Iterate()) { // RA2: as above
		cptr->Recalc_Attributes(-1); // RA2: as above
	}

	if (RMGCallback != NULL) RMGCallback();

	TiberiumClass::Init_Tiberium_Growth_System(); // RA2: no veinhole growth system
	TiberiumClass::Init_Tiberium_Spread_System();

	DebugString("RMG: Cleanup\n");

	SeededWaterAmount = 0;
	WorkingRegionID = 0;

	if (RMGCellData != NULL) {
		delete [] RMGCellData;
		RMGCellData = NULL;
	}

	for (index = MapRegionClass::MapRegions.Count() - 1; index >= 0; index--) { // RA2: as above
		MapRegionClass * region = MapRegionClass::MapRegions[index]; // RA2: as above
		if (region != NULL) {
			delete region;
		}
	}

	MapRegionClass::TotalCount = 0;
	Map.Overpass();
	DebugString("RMG: Compute Radar Image\n");
	Map.Set_Local_Dimensions(Map.LocalRect);
	Map.Compute_Radar_Image();

	Update_Progress(100);

	DebugString("RMG: Done\n");

	if (show_progress) { // RA2: the progress screen is closed again
		HWND control = GetDlgItem(dialog, 0x638); // RA2: as above
		if (control != NULL) { // RA2: as above
			ShowWindow(control, SW_HIDE); // RA2: as above
		}
		Update_Progress(0); // RA2: as above
		Progress.Clear_Dialog(); // RA2: 0x6203D0, the window is forgotten
	}
}
