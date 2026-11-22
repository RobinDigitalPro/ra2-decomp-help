// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00638C20 (24 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20d5a0 (VA 0x0060D5A0, 32 bytes incl. padding)
// RA2 symbol : ?Planning_Terminal_Mission@@YI_NH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7143)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Planning_Terminal_Mission(int mission) // RA2: 0x006159C0 (no function of its own); the missions that end a path
{
	return mission == 7 || mission == 8 || mission == 9; // RA2: as above
}
