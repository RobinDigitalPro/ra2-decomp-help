// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0079BED0 (122 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x344310 (VA 0x00744310, 128 bytes incl. padding)
// RA2 symbol : ?Is_Selected_Buddy_Known@@YI_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9412)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool Is_Selected_Buddy_Known(void) // RA2: 1.001 0x00744310, the status of the selected buddy is above 2
{
	if (g_SelectedBuddy.length() == 0) {
		return(false);
	}
	unsigned int state = 0;
	g_BuddyStatus.getValue(g_SelectedBuddy, state);
	if ((int)state >= 0 && (int)state <= 2) {
		return(false);
	}
	return(true);
}
