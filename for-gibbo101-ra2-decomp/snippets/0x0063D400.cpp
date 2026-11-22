// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063D400 (114 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x211d70 (VA 0x00611D70, 128 bytes incl. padding)
// RA2 symbol : ?Planning_Draw_Dot@@YIXVPoint2D@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8409)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Draw_Dot(Point2D center, int color) // RA2: 0x0061A190; draws a 6 by 6 frame around a pixel
{
	Rect view; // RA2: as above
	view = Get_Title_Screen_Area(); // RA2: as above
	Rect square; // RA2: as above
	square = Planning_Centered_Rect(center, 6); // RA2: as above
	CompositeSurface->Draw_Rect(view, square, color); // RA2: as above
}
