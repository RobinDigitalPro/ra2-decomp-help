// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00730530 (290 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2ea3f0 (VA 0x006EA3F0, 304 bytes incl. padding)
// RA2 symbol : ?Free_Sidebar_Rects@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9079)
// source TU  : src/m85/src/txtlabel2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: frees the areas the sidebar and the tab bar were laid out in.
/// </summary>
void __fastcall Free_Sidebar_Rects(void) // RA2: 0x006F5400
{
	operator delete(SidebarBackRect); // RA2: as above
	SidebarBackRect = NULL; // RA2: as above
	operator delete(TabBackRect); // RA2: as above
	TabBackRect = NULL; // RA2: as above
	operator delete(RadarFrameRect); // RA2: as above
	RadarFrameRect = NULL; // RA2: as above
	operator delete(RadarAnimRect); // RA2: as above
	RadarAnimRect = NULL; // RA2: as above
	operator delete(RadarAreaRect); // RA2: as above
	RadarAreaRect = NULL; // RA2: as above
	operator delete(Side1Rect); // RA2: as above
	Side1Rect = NULL; // RA2: as above
	operator delete(Free_Button_Strip); // RA2: as above
	Free_Button_Strip = NULL; // RA2: as above
	operator delete(Default_Button_Y); // RA2: as above
	Default_Button_Y = NULL; // RA2: as above
	operator delete(Default_Button_Strip); // RA2: as above
	Default_Button_Strip = NULL; // RA2: as above
	operator delete(SidebarButtonsRect); // RA2: as above
	SidebarButtonsRect = NULL; // RA2: as above
	operator delete(TabBarRect); // RA2: as above
	TabBarRect = NULL; // RA2: as above
	operator delete(TabLeftRect); // RA2: as above
	TabLeftRect = NULL; // RA2: as above
	operator delete(ThumbOpenRect); // RA2: as above
	ThumbOpenRect = NULL; // RA2: as above
	operator delete(ThumbClosedRect); // RA2: as above
	ThumbClosedRect = NULL; // RA2: as above
	operator delete(ButtonSlotRect); // RA2: as above
	ButtonSlotRect = NULL; // RA2: as above
	operator delete(TabEndRect); // RA2: as above
	TabEndRect = NULL; // RA2: as above
}
