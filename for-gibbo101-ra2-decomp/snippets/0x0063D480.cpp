// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063D480 (126 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x211df0 (VA 0x00611DF0, 128 bytes incl. padding)
// RA2 symbol : ?Planning_Fill_Dot@@YIXVPoint2D@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9767)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Fill_Dot(Point2D center, int color) // RA2: 0x0061A210; fills a 6 by 6 square around a pixel, less its edge
{
	Point2D point = center; // RA2: as above
	Rect view; // RA2: as above
	view = Get_Title_Screen_Area(); // RA2: as above
	Rect square; // RA2: as above
	square = Planning_Centered_Rect(point, 6); // RA2: as above
	Planning_Inflate(square, -1); // RA2: as above
	Surface * surface = CompositeSurface; // RA2: as above
	surface->Fill_Rect(view, square, color); // RA2: as above
}
