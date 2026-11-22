// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006370A0 (5 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20ba20 (VA 0x0060BA20, 16 bytes incl. padding)
// RA2 symbol : ?Planning_Reset_Wrapper@@YAXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.1538)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __cdecl Planning_Reset_Wrapper(void) // RA2: 0x00613E40
{
	Planning_Reset_State(); // RA2: as above
}
