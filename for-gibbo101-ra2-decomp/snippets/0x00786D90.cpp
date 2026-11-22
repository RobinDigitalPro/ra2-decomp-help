// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00786D90 (48 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x337310 (VA 0x00737310, 48 bytes incl. padding)
// RA2 symbol : ?Connect_To_Selected_Server@@YI_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool Connect_To_Selected_Server(void) // RA2: 0x00742D50, not in TibSun: connects to the server of the list the player picked, false when the index is not in the list
{
	if (g_CurrentServerIndex >= 1 && g_CurrentServerIndex < g_Servers.length()) { // RA2: as above
		Server * server = NULL; // RA2: as above
		g_Servers.getPointer(&server, g_CurrentServerIndex); // RA2: as above
		return(Connect_To_Server(server)); // RA2: a jump to Connect_To_Server
	}
	return(false); // RA2: as above
}
