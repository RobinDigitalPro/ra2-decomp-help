// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E64C0 (91 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c0630 (VA 0x005C0630, 96 bytes incl. padding)
// RA2 symbol : ?Get_Scenario_Slot_Limit@@YIHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9296)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Fetches how many players a scenario takes.
/// </summary>
/// <param name="index">Index into the multiplayer scenario list, -1 for none.</param>
/// <returns>Returns with the number of slots.</returns>
int __fastcall Get_Scenario_Slot_Limit(int index) // RA2: 0x005C65A0, not in TibSun; how many players a scenario takes in this game
{
	if (index == -1) { // RA2: as above
		return(8); // RA2: as above
	}
	int limit = RandomMapWaypointCount(index); // RA2: as above
	if (Session.MPGameMode != NULL) { // RA2: as above
		int mode_limit = Session.MPGameMode->vt_entry_80(); // RA2: as above
		if (mode_limit != -1 && mode_limit < limit) { // RA2: as above
			limit = mode_limit; // RA2: as above
		}
	}
	if (Session.Type == GAME_INTERNET) { // RA2: as above
		if (Is_Current_Channel_Flag_8()) { // RA2: as above
			limit &= ~1; // RA2: as above
		} else if (Is_Current_Channel_Tournament()) { // RA2: as above
			limit = 2; // RA2: as above
		}
	}
	return(limit); // RA2: as above
}
