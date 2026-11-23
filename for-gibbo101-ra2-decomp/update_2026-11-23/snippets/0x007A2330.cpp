// ra2-decomp help snippet, update 2026-11-23 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007A2330 (706 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0x349dd0 (VA 0x00749DD0, 578 bytes without padding)
// RA2 symbol : ?Setup_Match_Map@@YIXPBD@Z
// similarity : 0.8529 (similar, masked instruction tokens; shape 0.8529)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/wonline.cpp
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

void __fastcall Setup_Match_Map(char const * options) // RA2: 1.001 0x00749DD0, the two players of the "Start " message of the matching server (name, side, color each) and the random map of the match
{
	char buffer[256];
	strcpy(buffer, options);
	char * name = strtok(buffer, ":,");
	int house = atol(strtok(NULL, ","));
	int color = atol(strtok(NULL, ","));
	{
		Wstring player(name);
		Assign_House_And_Color(player, house, color);
	}
	name = strtok(NULL, ",");
	house = atol(strtok(NULL, ","));
	color = atol(strtok(NULL, ","));
	{
		Wstring player(name);
		Assign_House_And_Color(player, house, color);
	}

	strcpy(Session.ScenarioFileName, "RandMap.Sed");
	RandomMapGen.SeedData.NumPlayers = 4;
	Session.Options.ScenarioIndex = -1;
	HWND dialog = WS_Find_Dialog(0x11F);
	Do_Random_Map(dialog, Wait_Callback_Thunk);
	RandomMapGen.SeedData.Save("RandMap.Sed");

	int index;
	bool found = false;
	for (index = 0; index < Session.Scenarios.Count(); index++) {
		if (Session.Scenarios[index]->Is_Random_Map()) {
			found = true;
			break;
		}
	}
	char * digest = CalcRandomMapDigest();
	if (!found) {
		MultiMission * scenario = new MultiMission("RandMap.Sed", RandomMapGen.SeedData.MapDescription, digest, true);
		Session.Scenarios.Add(scenario);
	} else {
		Session.Scenarios[index]->Set_Digest(digest);
		Session.Scenarios[index]->Set_Description(RandomMapGen.SeedData.MapDescription);
	}
	delete digest;
	if (Set_Scenario_Info_From_Index(index) == true) {
		Session.Options.ScenarioIndex = index;
	}
}
