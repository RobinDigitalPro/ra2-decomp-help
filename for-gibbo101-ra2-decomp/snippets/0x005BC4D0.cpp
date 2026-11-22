// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005BC4D0 (92 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x19a8c0 (VA 0x0059A8C0, 96 bytes incl. padding)
// RA2 symbol : ?Debug_Window_Reset_Pages@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9459)
// source TU  : src/m85/src/motlib.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Debug_Window_Reset_Pages(void) // level-2 1.001: 0x19A8C0, adopted from gibbo101 (FUN_005BC4D0)
{
	for (int i = 0; i < 8; i++) {
		DebugPages[i]->Clear(); // level-2 1.001: inline
	}
}
