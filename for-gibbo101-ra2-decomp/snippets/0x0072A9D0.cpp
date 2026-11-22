// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0072A9D0 (11 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2e6bd0 (VA 0x006E6BD0, 16 bytes incl. padding)
// RA2 symbol : ?Assign_Point@@YIXPAVPoint2D@@PBV1@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6667)
// source TU  : src/m85/src/txtlabel2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: assigns one point to another.
/// </summary>
void __fastcall Assign_Point(Point2D * dest, Point2D const * source) // RA2: 0x006F1AF0
{
	*dest = *source; // RA2: as above
}
