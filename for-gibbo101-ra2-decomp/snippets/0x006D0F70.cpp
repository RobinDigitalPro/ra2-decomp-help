// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006D0F70 (58 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x296e60 (VA 0x00696E60, 64 bytes incl. padding)
// RA2 symbol : ?Free_Button_Shapes@@YAXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8696)
// source TU  : src/m85/src/tab.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __cdecl Free_Button_Shapes(void)	// RA2: out-of-line copy of the loop DisposeOfArt has
{
	for (int index = 0; index < TabClass::BUTTON_COUNT; index++) {	// RA2: as above
		TabClass::Free_Button_Shape(index);	// RA2: as above
	}
}
