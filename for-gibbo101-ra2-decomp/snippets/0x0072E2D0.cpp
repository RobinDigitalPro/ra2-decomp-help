// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0072E2D0 (384 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2e84c0 (VA 0x006E84C0, 384 bytes incl. padding)
// RA2 symbol : ?Draw_Interface_Borders@@YIXPAVSurface@@ABV?$TRect@H@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/txtlabel2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: paints black over the screen outside the dialog frame when the screen is larger than 800 by 600.
/// </summary>
void __fastcall Draw_Interface_Borders(Surface * surface, Rect const & window) // RA2: 0x006F34D0
{
	if (VideoModeWidth >= 1024) { // RA2: as above
		int left = DialogBackRect->X; // RA2: as above
		int right = SlideTopRect->X + SlideTopRect->Width; // RA2: as above
		int top = DialogBackRect->Y; // RA2: as above
		int bottom = LowerScreenRect->Height + LowerScreenRect->Y; // RA2: as above
		Rect rect(0, 0, left, top); // RA2: as above
		surface->Fill_Rect(rect, window, 0); // RA2: as above
		rect = Rect(left, 0, 800, top); // RA2: as above
		surface->Fill_Rect(rect, window, 0); // RA2: as above
		rect = Rect(right, 0, left, top); // RA2: as above
		surface->Fill_Rect(rect, window, 0); // RA2: as above
		rect = Rect(right, top, left, 600); // RA2: as above
		surface->Fill_Rect(rect, window, 0); // RA2: as above
		rect = Rect(right, bottom, left, 600); // RA2: as above
		surface->Fill_Rect(rect, window, 0); // RA2: as above
		rect = Rect(left, bottom, 800, top); // RA2: as above
		surface->Fill_Rect(rect, window, 0); // RA2: as above
		rect = Rect(0, bottom, left, top); // RA2: as above
		surface->Fill_Rect(rect, window, 0); // RA2: as above
		rect = Rect(0, top, left, 600); // RA2: as above
		surface->Fill_Rect(rect, window, 0); // RA2: as above
	}
}
