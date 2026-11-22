// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006CFDB0 (57 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x295cc0 (VA 0x00695CC0, 64 bytes incl. padding)
// RA2 symbol : ?Set_Button_Count@TabClass@@SIXH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8372)
// source TU  : src/m85/src/tab.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void TabClass::Set_Button_Count(int count)	// RA2: sets the number of rows; the buttons' left edge is not left of the open thumb button's right edge
{
	ButtonRows = count;	// RA2: as above
	int left = TabEndRect->X - count * ButtonSlotRect->Width;	// RA2: as above
	int limit = ThumbOpenRect->X + ThumbOpenRect->Width;	// RA2: as above
	ButtonsLeft = left > limit ? left : limit;	// RA2: as above
}
