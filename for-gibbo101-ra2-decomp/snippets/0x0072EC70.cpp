// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0072EC70 (740 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2e8e60 (VA 0x006E8E60, 752 bytes incl. padding)
// RA2 symbol : ?Layout_Interface_Art@@YIXHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9746)
// source TU  : src/m85/src/txtlabel2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: works out where the parts of the dialog frame go on a screen of this size: the frame is 800 by 600 and
/// centred on larger screens.
/// </summary>
void __fastcall Layout_Interface_Art(int width, int height) // RA2: 0x006F3E70
{
	int left = 0; // RA2: as above
	int right = width; // RA2: as above
	if (width >= 1024) { // RA2: as above
		left = (width - 800) / 2; // RA2: as above
		right = width - left; // RA2: as above
	}
	int top = 0; // RA2: as above
	int bottom = height; // RA2: as above
	int span = height; // RA2: as above
	if (height >= 768) { // RA2: as above
		top = (height - 600) / 2; // RA2: as above
		bottom = height - top; // RA2: as above
		span = height - top * 2; // RA2: as above
	}
	bool small_width = width == 640; // RA2: as above
	bool small_height = height == 480; // RA2: as above

	int w = small_width ? Art_Dialog_Back640->Get_Width() : Art_Dialog_Back->Get_Width(); // RA2: as above
	int h = small_height ? Art_Dialog_Back640->Get_Height() : Art_Dialog_Back->Get_Height(); // RA2: as above
	DialogBackRect = new Rect(left, top, w, h); // RA2: as above

	int tw = ArtSlideTop->Get_Width(); // RA2: as above
	int th = ArtSlideTop->Get_Height(); // RA2: as above
	int x = right - tw; // RA2: as above
	SlideTopRect = new Rect(x, top, tw, th); // RA2: as above

	int wh = ArtSlideWarning->Get_Height(); // RA2: as above
	SlideWarningRect = new Rect(x, top, tw, wh); // RA2: as above

	int by = SlideTopRect->Height + top; // RA2: as above
	int bh = ArtSlideButtonBack->Get_Height(); // RA2: as above
	Button_Strip_Top = new Rect(x, by, tw, bh); // RA2: as above

	int aw = Slide_Button_Shape->Get_Width(); // RA2: as above
	int ah = Slide_Button_Shape->Get_Height(); // RA2: as above
	int ax = Button_Strip_Top->Width - aw + Button_Strip_Top->X; // RA2: as above
	int ay = Button_Strip_Top->Y; // RA2: as above
	SlideButtonRect = new Rect(ax, ay, aw, ah); // RA2: as above

	int mw = ArtSlideMPButton->Get_Width(); // RA2: as above
	int mh = ArtSlideMPButton->Get_Height(); // RA2: as above
	int my = Button_Strip_Top->Height + Button_Strip_Top->Y - mh; // RA2: as above
	SlideMPButtonRect = new Rect(right - mw, my, mw, mh); // RA2: as above

	SlideButtonCount = (span - SlideTopRect->Height) / Button_Strip_Top->Height; // RA2: as above
	int offset = Button_Strip_Top->Height * SlideButtonCount; // RA2: as above
	int used = SlideTopRect->Height + offset; // RA2: as above
	int ly = Button_Strip_Top->Y + offset; // RA2: as above
	int lw = ArtSlideBottom->Get_Width(); // RA2: as above
	Button_Strip_Bottom = new Rect(right - lw, ly, lw, span - used); // RA2: as above

	int sw = small_width ? ArtLowerScreen640->Get_Width() : ArtLowerScreen->Get_Width(); // RA2: as above
	int sh = small_height ? ArtLowerScreen640->Get_Height() : ArtLowerScreen->Get_Height(); // RA2: as above
	LowerScreenRect = new Rect(left, bottom - sh, sw, sh); // RA2: as above
}
