// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006CFD60 (71 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x295c70 (VA 0x00695C70, 80 bytes incl. padding)
// RA2 symbol : ?Get_Button_Rect@TabClass@@SI?AV?$TRect@H@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8475)
// source TU  : src/m85/src/tab.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

Rect TabClass::Get_Button_Rect(int command)	// RA2: the first slot rectangle moved by the command's position
{
	Rect rect = *ButtonSlotRect;	// RA2: as above
	return(Rect(SlotButton[command] * SlotPitch + rect.X, SlotTop, rect.Width, rect.Height));	// RA2: as above
}
