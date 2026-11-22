// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007A2330 (706 bytes; gibbo status: attempted-partial 99.1%)
// RA2 RVA    : 0x349dd0 (VA 0x00749DD0, 592 bytes incl. padding)
// RA2 symbol : ?Setup_Match_Map@@YIXPBD@Z
// similarity : 0.8529 (similar, masked instruction tokens; shape 0.8337)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

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
