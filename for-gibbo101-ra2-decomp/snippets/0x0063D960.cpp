// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063D960 (86 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2122d0 (VA 0x006122D0, 96 bytes incl. padding)
// RA2 symbol : ?Planning_Draw_Dashed_Thick_Line@@YIXVPoint2D@@0HH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8958)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Draw_Dashed_Thick_Line(Point2D start, Point2D end, int thickness, int color) // RA2: 0x0061A6F0; draws a dashed line thickness less 2 pixels wide
{
	int count = thickness - 2; // RA2: as above
	int first; // RA2: as above
	int last; // RA2: as above
	if (count <= 0) { // RA2: as above
		first = 0; // RA2: as above
		last = 0; // RA2: as above
	} else { // RA2: as above
		last = count / 2; // RA2: as above
		first = last - count + 1; // RA2: as above
	}
	for (int offset = first; offset <= last; offset++) { // RA2: as above
		Planning_Draw_Line(start, end, offset, color, true); // RA2: as above
	}
}
