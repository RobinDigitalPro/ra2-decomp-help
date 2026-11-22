// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00634510 (53 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x208eb0 (VA 0x00608EB0, 64 bytes incl. padding)
// RA2 symbol : ?Planning_Centered_Rect@@YI?AV?$TRect@H@@VPoint2D@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8070)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

Rect __fastcall Planning_Centered_Rect(Point2D center, int size) // RA2: 0x006112D0; a size by size rectangle centered on a pixel
{
	int offset = -(size / 2); // RA2: as above
	Point2D corner = center; // RA2: as above
	corner.X += offset; // RA2: as above
	corner.Y += offset; // RA2: as above
	assert(size > 0); // level-2: assert inferred from VC6 inline budget (with the constructor, Hit_Test and Lead_Box_Rect2 keep this function out of line)
	Rect rect(corner.X, corner.Y, size, size); // level-2 1.001: the constructor, which Planning_Mouse_AI calls out of line (0x42bcd0) // RA2: as above
	return rect; // RA2: as above
}
