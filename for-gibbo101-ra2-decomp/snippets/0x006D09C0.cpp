// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006D09C0 (83 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2968b0 (VA 0x006968B0, 96 bytes incl. padding)
// RA2 symbol : ?Add_Button_ToolTip@TabClass@@SIXPAVControlClass@@PBD@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7869)
// source TU  : src/m85/src/tab.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void TabClass::Add_Button_ToolTip(ControlClass * control, char const * label)	// RA2: registers a control's tool tip under its ID with a label
{
	if (control != NULL) {	// RA2: as above
		ToolTip tip;	// RA2: as above
		tip.ID = control->ID;	// RA2: as above
		tip.Text = (int)label;	// RA2: as above
		tip.Region.X = control->X;	// RA2: as above
		tip.Region.Y = control->Y;	// RA2: as above
		tip.Region.Width = control->Width;	// RA2: as above
		tip.Region.Height = control->Height;	// RA2: as above
		ToolTips->Remove(control->ID);	// RA2: as above
		ToolTips->Add(&tip);	// RA2: as above
	}
}
