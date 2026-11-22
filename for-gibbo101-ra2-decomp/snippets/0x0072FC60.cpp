// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0072FC60 (1179 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2e9c80 (VA 0x006E9C80, 1216 bytes incl. padding)
// RA2 symbol : ?Layout_Sidebar_Art@@YIXHH@Z
// similarity : 0.9727 (very-similar, masked instruction tokens; shape 0.9772)
// source TU  : src/m85/src/txtlabel2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: works out where the parts of the sidebar and of the tab bar go on a screen of this size.
/// </summary>
void __fastcall Layout_Sidebar_Art(int width, int height) // RA2: 0x006F4C90
{
	ShapeSet * backdrop; // RA2: as above
	if (VideoModeWidth == 640) { // RA2: as above
		backdrop = ArtSidebarBack640; // RA2: as above
	} else if (VideoModeWidth == 800) { // RA2: as above
		backdrop = ArtSidebarBack800; // RA2: as above
	} else {
		backdrop = ArtSidebarBack1024; // RA2: as above
	}
	int w = backdrop->Get_Width(); // RA2: as above
	int h = backdrop->Get_Height(); // RA2: as above
	SidebarBackRect = new Rect(0, 0, w, h); // RA2: as above

	w = TabBackShape->Get_Width(); // RA2: as above
	h = TabBackShape->Get_Height(); // RA2: as above
	int x = width - w; // RA2: as above
	TabBackRect = new Rect(x, 0, w, h); // RA2: as above
	int y = h; // RA2: as above
	h = RadarFrameShape->Get_Height(); // RA2: as above
	RadarFrameRect = new Rect(x, y, w, h); // RA2: as above
	y += h; // RA2: as above
	h = RadarAnimShape->Get_Height(); // RA2: as above
	RadarAnimRect = new Rect(x, y, w, h); // RA2: as above
	y += h; // RA2: as above
	h = ArtSide1->Get_Height(); // RA2: as above
	Side1Rect = new Rect(x, y, w, h); // RA2: as above
	y += h; // RA2: as above
	h = ArtSide2->Get_Height(); // RA2: as above
	Free_Button_Strip = new Rect(x, y, w, h); // RA2: as above
	h = ArtSide3->Get_Height(); // RA2: as above
	Default_Button_Y = new Rect(x, y, w, h); // RA2: as above
	h = ArtAddon->Get_Height(); // RA2: as above
	Default_Button_Strip = new Rect(x, y, w, h); // RA2: as above

	SidebarStripCount = (height - Default_Button_Y->Height - Side1Rect->Height - RadarAnimRect->Height
		- RadarFrameRect->Height - TabBackRect->Height) / Free_Button_Strip->Height; // RA2: as above
	y += SidebarStripCount * Free_Button_Strip->Height; // RA2: as above
	Default_Button_Y->Y = y; // RA2: as above
	Default_Button_Strip->Y = Default_Button_Y->Height + y; // RA2: as above

	y = height - 32; // RA2: as above
	int bar_width = Get_Title_Screen_Area().Width; // RA2: as above
	TabBarRect = new Rect(0, y, bar_width, 32); // RA2: as above
	w = TabLeftShape->Get_Width(); // RA2: as above
	h = TabLeftShape->Get_Height(); // RA2: as above
	TabLeftRect = new Rect(0, y, w, h); // RA2: as above
	w = TabThumbShape->Get_Width(); // RA2: as above
	h = TabThumbShape->Get_Height(); // RA2: as above
	ThumbOpenRect = new Rect(0, y, w, h); // RA2: as above
	ThumbClosedRect = new Rect(0, y, w, h); // RA2: as above
	w = TabTileShape->Get_Width(); // RA2: as above
	h = TabTileShape->Get_Height(); // RA2: as above
	ButtonSlotRect = new Rect(0, y, w, h); // RA2: as above
	w = TabRightShape->Get_Width(); // RA2: as above
	h = TabRightShape->Get_Height(); // RA2: as above
	TabEndRect = new Rect(0, y, w, h); // RA2: as above

	TabTileCount = (width - ThumbOpenRect->Width - TabBackRect->Width - TabEndRect->Width)
		/ ButtonSlotRect->Width; // RA2: as above
	int bar_x = TabBackRect->X - TabEndRect->Width; // RA2: as above
	TabEndRect->X = bar_x; // RA2: as above
	bar_x -= ButtonSlotRect->Width * TabTileCount; // RA2: as above
	ButtonSlotRect->X = bar_x; // RA2: as above
	bar_x -= ThumbOpenRect->Width; // RA2: as above
	ThumbOpenRect->X = bar_x; // RA2: as above
	ThumbOpenX = bar_x; // RA2: as above
	int tab_x = TabEndRect->X - ThumbClosedRect->Width; // RA2: as above
	ThumbClosedRect->X = tab_x; // RA2: as above
	ThumbClosedX = tab_x; // RA2: as above
	ThumbTravel = TabEndRect->X - ThumbOpenRect->Width - ThumbOpenRect->X; // RA2: as above

	int column_x = RadarFrameRect->X; // RA2: as above
	int column_y = RadarFrameRect->Y; // RA2: as above
	int column_width = RadarFrameRect->Width; // RA2: as above
	int column_height = RadarAnimRect->Height + RadarFrameRect->Height; // RA2: as above
	RadarAreaRect = new Rect(column_x, column_y, column_width, column_height); // RA2: as above
	int strip_x = Side1Rect->X; // RA2: as above
	int strip_y = Side1Rect->Y; // RA2: as above
	int strip_width = Side1Rect->Width; // RA2: as above
	int strip_height = SidebarStripCount * Free_Button_Strip->Height + Default_Button_Y->Height + Side1Rect->Height; // RA2: as above
	SidebarButtonsRect = new Rect(strip_x, strip_y, strip_width, strip_height); // RA2: as above
}
