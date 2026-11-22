// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006D14F0 (116 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2973e0 (VA 0x006973E0, 128 bytes incl. padding)
// RA2 symbol : ?Hide_Buttons@TabClass@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8667)
// source TU  : src/m85/src/tab.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void TabClass::Hide_Buttons(void)	// RA2: removes the open bar's buttons and their tool tips
{
	Remove_Command_Buttons();	// RA2: as above
	Remove_A_Button(ThumbOpenButton);	// RA2: as above
	for (int command = 0; command < BUTTON_COUNT; command++) {	// RA2: as above
		ShapeButtonClass * button = Get_Button(command);	// RA2: as above
		if (button != NULL) {	// RA2: as above
			ToolTips->Remove(button->ID);	// RA2: as above
		}
	}
	ToolTips->Remove(BUTTON_THUMB_OPEN);	// RA2: as above
}
