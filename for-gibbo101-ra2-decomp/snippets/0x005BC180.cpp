// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005BC180 (382 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x19a570 (VA 0x0059A570, 384 bytes incl. padding)
// RA2 symbol : ?Debug_Window_Init@@YIXPAUHINSTANCE__@@PAUHWND__@@_N@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9912)
// source TU  : src/m85/src/motlib.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Debug_Window_Init(HINSTANCE instance, HWND window, bool enabled) // level-2 1.001: 0x19A570, adopted from gibbo101 (FUN_005BC180)
{
	DebugInstance = instance;
	DebugParentWindow = window;
	DebugEnabled = enabled;
	for (int i = 0; i < 8; i++) {
		DebugPages[i] = new DebugPage(i);
	}
	CurrentDebugPage = DebugPages[0];
	for (int j = 0; j < 8; j++) {
		DebugPages[j]->Clear(); // level-2 1.001: inline
	}
	if (DebugShowPending && DebugEnabled) {
		if (DebugWindow == NULL) {
			Create_Debug_Window();
		}
		DebugVisible = true;
		ShowWindow(DebugWindow, SW_SHOWNORMAL);
		SetFocus(DebugParentWindow);
	}
}
