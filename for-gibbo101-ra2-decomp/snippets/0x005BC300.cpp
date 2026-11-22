// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005BC300 (105 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x19a6f0 (VA 0x0059A6F0, 112 bytes incl. padding)
// RA2 symbol : ?Debug_Window_Shutdown@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8852)
// source TU  : src/m85/src/motlib.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Debug_Window_Shutdown(void) // level-2 1.001: 0x19A6F0, adopted from gibbo101 (FUN_005BC300)
{
	for (int i = 0; i < 8; i++) {
		if (DebugPages[i] != NULL) {
			delete DebugPages[i];
			DebugPages[i] = NULL;
		}
	}
	if (DebugWindow != NULL) {
		DeleteObject(DebugFont);
		Release_Debug_Window_Style(DebugWindow);
		DestroyWindow(DebugWindow);
		DebugFont = NULL;
		DebugWindow = NULL;
	}
}
