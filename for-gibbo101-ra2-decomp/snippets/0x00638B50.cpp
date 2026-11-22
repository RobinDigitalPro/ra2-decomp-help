// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00638B50 (24 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20d4d0 (VA 0x0060D4D0, 32 bytes incl. padding)
// RA2 symbol : ?Planning_Stop_Type@@YI_ND@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7143)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Planning_Stop_Type(char type) // RA2: 0x006158F0; the order types planning mode refuses: deploy, stop and scatter
{
	return type == 9 || type == 6 || type == 7; // RA2: as above
}
