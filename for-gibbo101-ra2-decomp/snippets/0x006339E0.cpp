// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006339E0 (59 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x208380 (VA 0x00608380, 64 bytes incl. padding)
// RA2 symbol : ?Planning_Coord_Pixel@@YI?AVPoint2D@@ABVCoord@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8889)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

Point2D __fastcall Planning_Coord_Pixel(Coord const & coord) // RA2: 0x006107A0; a coordinate as a pixel of the tactical view moved to the screen
{
	Point2D pixel; // RA2: as above
	TacticalMap->Coord_To_Pixel(coord, pixel); // RA2: as above
	pixel.X += TacticalRect.X; // RA2: as above
	pixel.Y += TacticalRect.Y; // RA2: as above
	return pixel; // RA2: as above
}
