// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063D560 (202 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x211ed0 (VA 0x00611ED0, 208 bytes incl. padding)
// RA2 symbol : ?Planning_Draw_Midpoint@@YIXVPoint2D@@0H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9600)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Draw_Midpoint(Point2D start, Point2D end, int color) // RA2: 0x0061A2F0; draws a 21 by 21 frame halfway along a line when it is at least 37 pixels long
{
	if (start.Distance_To(end) >= 37) { // RA2: as above; level-2 1.001: the length tested directly, as in Draw_Midpoint_Shape (the copy inlined in Planning_Draw_Node then loads the sums in the 1.001 order)
		int x = (start.X + end.X) / 2 - 10; // RA2: as above
		int y = (start.Y + end.Y) / 2 - 10; // RA2: as above
		Rect view = Get_Title_Screen_Area(); // RA2: as above
		Rect square(x, y, 21, 21); // RA2: as above
		CompositeSurface->Draw_Rect(view, square, color); // RA2: as above
	}
}
