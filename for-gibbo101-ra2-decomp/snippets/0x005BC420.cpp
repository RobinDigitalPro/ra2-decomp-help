// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005BC420 (27 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x19a810 (VA 0x0059A810, 32 bytes incl. padding)
// RA2 symbol : ?Debug_Window_Is_Shown@@YIHXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8000)
// source TU  : src/m85/src/motlib.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __fastcall Debug_Window_Is_Shown(void) // level-2 1.001: 0x19A810, adopted from gibbo101 (FUN_005BC420)
{
	if (DebugVisible || DebugShowPending) {
		return 1;
	}
	return 0;
}
