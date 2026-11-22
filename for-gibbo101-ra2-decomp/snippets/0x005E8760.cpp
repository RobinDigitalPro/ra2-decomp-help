// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E8760 (30 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c2560 (VA 0x005C2560, 32 bytes incl. padding)
// RA2 symbol : ?Is_Host@@YI_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9091)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Is_Host(void) // RA2: 0x005C86A0, not in TibSun; the local handle is the game's name
{
	wchar_t * handle = Narrow_To_Wide(Session.Handle); // RA2: the handle is widened before the game's name is pushed
	return(wcscmp(handle, Session.GameName) == 0); // RA2: as above
}
