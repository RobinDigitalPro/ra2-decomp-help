// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063D910 (67 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x212280 (VA 0x00612280, 80 bytes incl. padding)
// RA2 symbol : ?Planning_Draw_Thick_Line@@YIXVPoint2D@@0HH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8434)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Draw_Thick_Line(Point2D start, Point2D end, int thickness, int color) // RA2: 0x0061A6A0; draws a solid line thickness pixels wide
{
	int last = thickness / 2; // RA2: as above
	for (int offset = last - thickness + 1; offset <= last; offset++) { // RA2: as above
		Planning_Draw_Line(start, end, offset, color, false); // RA2: as above
	}
}
