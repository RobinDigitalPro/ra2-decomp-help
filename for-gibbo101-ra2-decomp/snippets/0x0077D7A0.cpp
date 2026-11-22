// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0077D7A0 (119 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x330c80 (VA 0x00730C80, 128 bytes incl. padding)
// RA2 symbol : ?Set_Lobby_Music@@YIX_N@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8861)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Set_Lobby_Music(bool online) // RA2: 0x0073C1B0, restarts the lobby score (theme -2) or queues theme -3
{
	if (online) { // RA2: as above
		if (!Theme.Still_Playing()) { // RA2: as above
			Theme.Stop();
			Theme.Queue_Song((ThemeType)-2); // RA2: as above
			return;
		}
		if (Theme.What_Is_Playing() == Theme.From_Name("INTRO")) { // RA2: as above
			Theme.Stop();
			Theme.Queue_Song((ThemeType)-2); // RA2: as above
		}
	} else {
		Theme.Queue_Song((ThemeType)-3); // RA2: as above
	}
}
