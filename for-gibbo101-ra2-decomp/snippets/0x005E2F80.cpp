// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E2F80 (21 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1be010 (VA 0x005BE010, 32 bytes incl. padding)
// RA2 symbol : ?Get_Current_Game_Mode@@YIPAVMultiplayerGameMode@@XZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5217)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Fetches the game mode the session options name.
/// The first game mode of the list is used when the options name none that exists.
/// </summary>
/// <returns>Returns with the current game mode.</returns>
MultiplayerGameMode * Get_Current_Game_Mode(void) // RA2: 0x005C34D0, TibSun has no such routine
{
	MultiplayerGameMode * mode = MultiplayerGameMode::Get(Session.Options.MPModeIndex); // RA2: as above
	if (mode == NULL) { // RA2: as above
		mode = First_Game_Mode(); // RA2: as above
	}
	return(mode); // RA2: as above
}
