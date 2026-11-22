// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E8720 (20 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c2520 (VA 0x005C2520, 32 bytes incl. padding)
// RA2 symbol : ?Is_Host_Name@@YI_NPBG@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5714)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Tells whether a name is the host's name.
/// </summary>
bool __fastcall Is_Host_Name(wchar_t const * name) // RA2: 0x005C8660, not in TibSun; the host is the game's name (Session.GameName)
{
	return(wcscmp(name, Session.GameName) == 0); // RA2: as above
}
