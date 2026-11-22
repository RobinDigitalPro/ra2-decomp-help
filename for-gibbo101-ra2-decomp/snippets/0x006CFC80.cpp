// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006CFC80 (49 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x295b90 (VA 0x00695B90, 64 bytes incl. padding)
// RA2 symbol : ?Free_Button_Shape@TabClass@@SIXH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6341)
// source TU  : src/m85/src/tab.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void TabClass::Free_Button_Shape(int index)	// RA2: frees the button shape when it was loaded rather than retrieved
{
	if (ButtonShapeAllocated[index]) {	// RA2: as above
		delete [] (char *)ButtonShapes[index];	// RA2: as above
		ButtonShapeAllocated[index] = false;	// RA2: as above
	}
	ButtonShapes[index] = NULL;	// RA2: as above
}
