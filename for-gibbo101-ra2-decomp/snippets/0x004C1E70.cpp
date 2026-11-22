// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004C1E70 (171 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xb1560 (VA 0x004B1560, 176 bytes incl. padding)
// RA2 symbol : ?Draw_Line@EBolt@@QAEXVCoord@@0HHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9565)
// source TU  : src/m85/src/ebolt.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Draws one depth shaded line of the bolt; the depth at each end is lowered by the height of that end.
/// </summary>
void EBolt::Draw_Line(Coord start, Coord end, int color, int start_depth, int end_depth) // RA2: 0x004B1850
{
	Point2D p1; // RA2: as above
	Point2D p2; // RA2: as above
	TacticalMap->Coord_To_Pixel(start, p1); // RA2: as above
	TacticalMap->Coord_To_Pixel(end, p2); // RA2: as above
	int d1 = start_depth - Tactical::Z_Lepton_To_Pixel(start.Z) - 2; // RA2: as above
	int d2 = end_depth - Tactical::Z_Lepton_To_Pixel(end.Z) - 2; // RA2: as above
	int pixel = NormalDrawer->Convert_Pixel(color); // RA2: as above
	CompositeSurface->Draw_Depth_Shaded_Line(TacticalRect, p1, p2, pixel, d1, d2); // RA2: as above
}
