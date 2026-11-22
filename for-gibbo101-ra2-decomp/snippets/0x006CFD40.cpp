// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006CFD40 (31 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x295c50 (VA 0x00695C50, 32 bytes incl. padding)
// RA2 symbol : ?Get_Button@TabClass@@SIPAVShapeButtonClass@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9565)
// source TU  : src/m85/src/tab.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

ShapeButtonClass * TabClass::Get_Button(int command)	// RA2: the button a command is on, or none when its position is out of range
{
	if (SlotButton[command] >= 0 && SlotButton[command] < BUTTON_COUNT) {	// RA2: the position is read three times in the source; the extra source size is what keeps this call out of line in AI's inlined Hide_Buttons loop
		return(&CommandButtons[SlotButton[command]]);	// RA2: as above
	}
	return(NULL);	// RA2: as above
}
