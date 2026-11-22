// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005BC370 (75 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x19a760 (VA 0x0059A760, 80 bytes incl. padding)
// RA2 symbol : ?Debug_Window_Show_Or_Defer@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8936)
// source TU  : src/m85/src/motlib.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Debug_Window_Show_Or_Defer(void) // level-2 1.001: 0x19A760, adopted from gibbo101 (FUN_005BC370)
{
	if (DebugParentWindow == NULL) {
		DebugShowPending = true;
		return;
	}
	if (DebugEnabled) {
		if (DebugWindow == NULL) {
			Create_Debug_Window();
		}
		DebugVisible = true;
		ShowWindow(DebugWindow, SW_SHOWNORMAL);
		SetFocus(DebugParentWindow);
	}
}
