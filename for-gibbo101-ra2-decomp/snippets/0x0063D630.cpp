// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063D630 (474 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x211fa0 (VA 0x00611FA0, 480 bytes incl. padding)
// RA2 symbol : ?Planning_Draw_Midpoint_Shape@@YIXVPoint2D@@0HHH@Z
// similarity : 0.9904 (very-similar, masked instruction tokens; shape 0.9688)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Draw_Midpoint_Shape(Point2D start, Point2D end, int color, int fill, int frame) // RA2: 0x0061A3C0; draws a framed and filled 21 by 21 box halfway along a line when it is at least 37 pixels long, with a cursor shape in it
{
	if (start.Distance_To(end) >= 37) { // RA2: as above
		int x = (start.X + end.X) / 2; // RA2: as above
		int y = (start.Y + end.Y) / 2; // RA2: as above
		int left = x - 10; // RA2: as above
		int top = y - 10; // RA2: as above
		Rect view = Get_Title_Screen_Area(); // RA2: as above
		Rect square(left, top, 21, 21); // RA2: as above
		Planning_Inflate(square, -1); // RA2: as above
		CompositeSurface->Draw_Rect(view, square, color); // RA2: as above
		Planning_Inflate(square, -1); // RA2: as above
		CompositeSurface->Fill_Rect(view, square, fill); // RA2: as above
		Point2D point(left, top); // RA2: as above
		Rect window = view; // RA2: as above
		ShapeSet const * shape = MouseClass::MouseShapes; // RA2: as above
		int width = shape->Get_Width(); // RA2: as above
		int height = shape->Get_Height(); // RA2: as above
		point.X = x - width / 2 - 1; // RA2: as above
		point.Y = y - height / 2; // RA2: as above
		Draw_Shape(*CompositeSurface, *MouseDrawer, shape, frame, point, window, SHAPE_WIN_REL, NULL, 0, ZGRAD_GROUND, 1000, NULL, 0, Point2D(0, 0)); // RA2: as above
	}
}
