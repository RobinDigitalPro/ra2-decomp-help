// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00705270 (1508 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2c6330 (VA 0x006C6330, 1520 bytes incl. padding)
// RA2 symbol : ?Draw_Shaded_Line@TechnoClass@@QBEXVCoord@@0VRGBClass@@_N@Z
// similarity : 0.9882 (very-similar, masked instruction tokens; shape 0.9860)
// source TU  : src/m85/src/techno.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Draws a line between two spots in 64 pieces that fade from the colour to black, with end markers
/// and an optional drop shadow.
/// </summary>
void TechnoClass::Draw_Shaded_Line(Coord start, Coord end, RGBClass color, bool shadow) const // RA2: not in TibSun, at 0x6D0DC0
{
	RGBClass shade; // RA2: the fade colour is zeroed on entry and assigned in the loop
	Point2D start_point;
	Point2D end_point;
	TacticalMap->Coord_To_Pixel(start, start_point);
	TacticalMap->Coord_To_Pixel(end, end_point);
	start_point.Y += TacticalRect.Y;
	end_point.Y += TacticalRect.Y;
	int pixel = DSurface::Build_Hicolor_Pixel(color);
	int fade = DSurface::Build_Hicolor_Pixel(BlackColor);
	Point2D shadow_start = start_point;
	shadow_start.Y += 1;
	Point2D shadow_end = end_point;
	shadow_end.Y += 1;
	if (shadow) {
		CompositeSurface->Fill_Rect(Intersect(TacticalRect, Moved_Rect(Rect(-2, -2, 3, 3), shadow_start)), pixel); // RA2: the end marker is a moved 3x3 rectangle (the exe builds it through the rectangle constructor)
		CompositeSurface->Fill_Rect(Intersect(TacticalRect, Moved_Rect(Rect(-2, -2, 3, 3), shadow_end)), fade); // RA2: the end marker is a moved 3x3 rectangle (the exe builds it through the rectangle constructor)
	}
	Rect clip = TacticalRect;
	if (shadow && Clip_Line_To_Rect(shadow_start, shadow_end, clip)) {
		CompositeSurface->Draw_Line(shadow_start, shadow_end, NormalDrawer->Convert_Pixel(0));
	}
	CompositeSurface->Fill_Rect(Intersect(TacticalRect, Target_Laser_Rect(start_point)), fade); // level-2 1.001: as gibbo101 ra2-decomp src/techno.cpp (commit f8916323fcb0cbb0df1821530bd65afa7b0df804, FUN_00705270), the end markers through Target_Laser_Rect
	CompositeSurface->Fill_Rect(Intersect(TacticalRect, Target_Laser_Rect(end_point)), pixel);
	Coord last = start;
	Coord next; // level-2 1.001: declared outside the loop, as gibbo101's FUN_00705270
	for (int i = 1, j = 63; i <= 64; i++, j--) {
		next.X = (start.X * j + end.X * i) / 64;
		next.Y = (start.Y * j + end.Y * i) / 64;
		next.Z = (start.Z * j + end.Z * i) / 64;
		TacticalMap->Coord_To_Pixel(last, start_point);
		TacticalMap->Coord_To_Pixel(next, end_point);
		start_point.Y += TacticalRect.Y;
		end_point.Y += TacticalRect.Y;
		if (Clip_Line_To_Rect(start_point, end_point, clip)) {
			shade = color; // RA2: the shade starts from the line color
			int ratio = j * 4;
			shade.Adjust(ratio < 0xFE ? ratio : 0xFE, BlackColor);
			CompositeSurface->Draw_Line(start_point, end_point, DSurface::Build_Hicolor_Pixel(shade));
		}
		last = next;
	}
}
