// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0072A9C0 (13 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2e6bc0 (VA 0x006E6BC0, 16 bytes incl. padding)
// RA2 symbol : ?Copy_Point@@YI?AVPoint2D@@PBV1@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8000)
// source TU  : src/m85/src/txtlabel2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

Point2D __fastcall Copy_Point(Point2D const * source) // RA2: 0x006F1AE0; a copy of a point
{
	Point2D result(source->X, source->Y); // RA2: as above
	return result; // RA2: as above
}
