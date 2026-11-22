// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0059BAB0 (268 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x17a090 (VA 0x0057A090, 272 bytes incl. padding)
// RA2 symbol : ?Cell_In_Generation_Shape@MapGeneratorClass@@QAE_NABVCell@@ABV?$TRect@H@@_NNN@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9789)
// source TU  : src/m85/src/mapgen.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: whether a cell lies in the area the spreader may grow over: the ellipse inscribed in the area when shaped,
/// else the area itself; anywhere when there is no area.
/// </summary>
bool MapGeneratorClass::Cell_In_Generation_Shape(Cell const & cell, Rect const & rect, bool shaped, double scale_x, double scale_y)
{
	if (rect == RECT_NONE) {
		return true;
	}
	if (shaped) {
		int a = cell.X - rect.X * 2 - cell.Y + Map.PlayRect.Width - 1;
		int b = cell.X - rect.Y * 2 - Map.PlayRect.Width + cell.Y - 1;
		double u = a * 0.5 - rect.Width * 0.5;
		double v = b * 0.5 - rect.Height * 0.5;
		return (u * u) * scale_x + (v * v) * scale_y < 1.0;
	}
	return rect.Is_Point_Within(Point2D(cell.X, cell.Y));
}
