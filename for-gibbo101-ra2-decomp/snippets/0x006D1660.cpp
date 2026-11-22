// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006D1660 (270 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x297550 (VA 0x00697550, 272 bytes incl. padding)
// RA2 symbol : ?Close_Thumb@TabClass@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9870)
// source TU  : src/m85/src/tab.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void TabClass::Close_Thumb(void)	// RA2: swaps the open bar's buttons for the closed bar's thumb button
{
	if (IsThumbActive) {	// RA2: as above
		Hide_Buttons();	// RA2: as above
		IsThumbActive = false;	// RA2: as above
		Show_Thumb_Button();	// RA2: as above
		IsToRedraw = true;	// RA2: as above
		Flag_To_Redraw(GS_REDRAW_DIRTY);	// RA2: as above
	}
}
