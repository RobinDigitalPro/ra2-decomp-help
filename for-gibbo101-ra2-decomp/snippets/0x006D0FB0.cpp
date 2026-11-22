// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006D0FB0 (29 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x296ea0 (VA 0x00696EA0, 32 bytes incl. padding)
// RA2 symbol : ?Init_Shape_Button@@YIXPAVShapeButtonClass@@HI@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8571)
// source TU  : src/m85/src/tab.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Init_Shape_Button(ShapeButtonClass * button, int id, unsigned flags)	// RA2: out-of-line copy of the button set-up the thumb buttons share
{
	button->ID = id;	// RA2: as above
	button->ShapeDrawer = SidebarDrawer;	// RA2: as above
	button->IsOn = false;	// RA2: as above
	button->IsToggleType = 0;	// RA2: as above
	button->Set_Flags(flags);	// RA2: as above
}
