// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006D1130 (204 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x297020 (VA 0x00697020, 208 bytes incl. padding)
// RA2 symbol : ?Setup_Thumb_Buttons@TabClass@@SAXXZ
// similarity : 0.9655 (very-similar, masked instruction tokens; shape 0.9667)
// source TU  : src/m85/src/tab.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __cdecl TabClass::Setup_Thumb_Buttons(void)	// RA2: out-of-line copy of the code Init_IO has
{
	ThumbOpenButton.ID = BUTTON_THUMB_OPEN;	// RA2: as above
	ThumbOpenButton.ShapeDrawer = SidebarDrawer;	// RA2: as above
	ThumbOpenButton.IsOn = false;	// RA2: as above
	ThumbOpenButton.IsToggleType = 0;	// RA2: as above
	ThumbOpenButton.Set_Flags(GadgetClass::LEFTPRESS | GadgetClass::LEFTRELEASE);	// RA2: as above
	ShapeSet const * shape = TabThumbShape;	// RA2: as above
	Rect area = *ThumbOpenRect;	// RA2: as above
	ThumbOpenButton.Set_Position(area.X, area.Y);	// RA2: as above
	ThumbOpenButton.Set_Shape(shape, 0, 0);	// RA2: as above

	ThumbClosedButton.ID = BUTTON_THUMB_CLOSED;	// RA2: as above
	ThumbClosedButton.ShapeDrawer = SidebarDrawer;	// RA2: as above
	ThumbClosedButton.IsOn = false;	// RA2: as above
	ThumbClosedButton.IsToggleType = 0;	// RA2: as above
	ThumbClosedButton.Set_Flags(GadgetClass::LEFTPRESS | GadgetClass::LEFTRELEASE);	// RA2: as above
	Rect area2 = *ThumbClosedRect;	// RA2: as above
	ThumbClosedButton.Set_Position(area2.X, area2.Y);	// RA2: as above
	ThumbClosedButton.Set_Shape(shape, 0, 0);	// RA2: as above
}
