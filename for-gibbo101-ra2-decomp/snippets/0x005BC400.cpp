// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005BC400 (32 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x19a7f0 (VA 0x0059A7F0, 32 bytes incl. padding)
// RA2 symbol : ?Debug_Window_Hide@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/motlib.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Debug_Window_Hide(void) // level-2 1.001: 0x19A7F0, adopted from gibbo101 (FUN_005BC400)
{
	DebugShowPending = false;
	if (DebugWindow != NULL) {
		DebugVisible = false;
		ShowWindow(DebugWindow, SW_HIDE);
	}
}
