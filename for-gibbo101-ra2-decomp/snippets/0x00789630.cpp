// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00789630 (103 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x3398a0 (VA 0x007398A0, 112 bytes incl. padding)
// RA2 symbol : ?Server_Name_Without_Prefix@@YI?AVWstring@@PBUServer@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8831)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

Wstring Server_Name_Without_Prefix(Server const * server) // RA2: 0x00745450, not in TibSun: the name of the server after the first colon (the part before it names the kind of server)
{
	Wstring name((char const *)server->name); // RA2: the server's name is copied into a Wstring
	Wstring token; // RA2: as above
	int position = name.getToken(0, ":", token); // RA2: the first token ends at the first colon
	if (position >= 0) { // RA2: as above
		name.remove(0, position + 1); // RA2: as above
	}
	return(name); // RA2: as above
}
