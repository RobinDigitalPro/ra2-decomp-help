// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006D1570 (116 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x297460 (VA 0x00697460, 128 bytes incl. padding)
// RA2 symbol : ?Show_Thumb_Button@TabClass@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8235)
// source TU  : src/m85/src/tab.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void TabClass::Show_Thumb_Button(void)	// RA2: adds the closed bar's thumb button and its tool tip
{
	Add_A_Button(ThumbClosedButton);	// RA2: as above
	Add_Button_ToolTip(&ThumbClosedButton, "Tip:ThumbClosed");	// RA2: as above
}
