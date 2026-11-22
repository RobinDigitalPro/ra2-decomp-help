// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00659590 (187 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x22cdb0 (VA 0x0062CDB0, 192 bytes incl. padding)
// RA2 symbol : ?Draw_Line@RadBeam@@QAEXABVCoord@@0F@Z
// similarity : 0.9831 (very-similar, masked instruction tokens; shape 0.9593)
// source TU  : src/m85/src/radbeam.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Draws one segment on the logical surface, clipped to the tactical view; the depth at each end follows the
/// beam's depth and the height of that end.
/// </summary>
void RadBeam::Draw_Line(Coord const & start, Coord const & end, short color) // RA2: 0x00635810
{
	Point2D first_pixel; // RA2: as above
	Point2D second_pixel; // RA2: as above
	TacticalMap->Coord_To_Pixel(start, first_pixel); // RA2: as above
	TacticalMap->Coord_To_Pixel(end, second_pixel); // RA2: as above
	Rect clip = TacticalRect; // RA2: as above
	if (Clip_Line_To_Rect(first_pixel, second_pixel, clip)) { // RA2: as above
		int first_z = Depth - Tactical::Z_Lepton_To_Pixel(start.Z) - 2; // RA2: as above
		int second_z = 0 - Tactical::Z_Lepton_To_Pixel(end.Z) - 2; // RA2: as above
		LogicalSurface->Draw_Depth_Shaded_Line(TacticalRect, first_pixel, second_pixel, color, first_z, second_z); // RA2: as above
	} // RA2: as above
}
