// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0072E8C0 (84 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2e8ab0 (VA 0x006E8AB0, 96 bytes incl. padding)
// RA2 symbol : ?Draw_Slide_Top@@YIXPAVSurface@@ABV?$TRect@H@@@Z
// similarity : 0.9552 (very-similar, masked instruction tokens; shape 0.8250)
// source TU  : src/m85/src/txtlabel2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: draws the second frame of the slide's top shape, at its place.
/// </summary>
void __fastcall Draw_Slide_Top(Surface * surface, Rect const & window) // RA2: 0x006F3AC0
{
	Point2D point(0, 0); // RA2: as above
	point.X = SlideTopRect->X; // RA2: as above
	point.Y = SlideTopRect->Y; // RA2: as above
	Draw_Shape(*surface, *ShellDrawer, ArtSlideTop, 1, point, window, ShapeFlags_Type(0x400), 0, 0, ZGradientType(0), 1000, 0, 0, Point2D(0, 0)); // RA2: as above
}
