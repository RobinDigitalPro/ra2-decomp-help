// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006D04D0 (31 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2963d0 (VA 0x006963D0, 32 bytes incl. padding)
// RA2 symbol : ?Remove_Command_Buttons@TabClass@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9655)
// source TU  : src/m85/src/tab.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void TabClass::Remove_Command_Buttons(void)	// RA2: removes the 25 command buttons
{
	for (int index = 0; index < BUTTON_COUNT; index++) {	// RA2: as above
		Remove_A_Button(CommandButtons[index]);	// RA2: as above
	}
}
