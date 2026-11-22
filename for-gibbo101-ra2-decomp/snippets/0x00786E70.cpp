// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00786E70 (117 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x3373f0 (VA 0x007373F0, 128 bytes incl. padding)
// RA2 symbol : ?Find_Server_Suffix@@YIHABVWstring@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8991)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int Find_Server_Suffix(Wstring const & name) // RA2: 0x00742E30, not in TibSun: the index of the server whose name is "<prefix>:" followed by this name, -1 when there is none
{
	if (name.length() != 0) { // RA2: as above
		for (int i = 1; i < g_Servers.length(); i++) { // RA2: as above
			Server * server = NULL; // RA2: as above
			g_Servers.getPointer(&server, i); // RA2: as above
			char * separator = strchr((char *)server->name, ':'); // RA2: as above
			if (separator && *separator && name == (separator + 1)) { // RA2: as above
				return(i);
			}
		}
	}
	return(-1); // RA2: as above
}
