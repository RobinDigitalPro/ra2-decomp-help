// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E8740 (28 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c2540 (VA 0x005C2540, 32 bytes incl. padding)
// RA2 symbol : ?Is_Host_Player@UI@@YI_NH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8333)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Is_Host_Player(int player) // RA2: 0x005C8680, not in TibSun; the player of the list is the host
{
	return(wcscmp(Session.Players[player]->Name, Session.GameName) == 0); // RA2: as above
}
