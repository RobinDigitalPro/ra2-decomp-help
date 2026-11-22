// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0059B940 (356 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x179f20 (VA 0x00579F20, 368 bytes incl. padding)
// RA2 symbol : ?Direction_Weighted_Cell_Distance@MapGeneratorClass@@QAENABVCell@@0ABV?$TRect@H@@0MM@Z
// similarity : 0.9845 (very-similar, masked instruction tokens; shape 0.9556)
// source TU  : src/m85/src/mapgen.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: the spreader's score for stepping to a cell. Inside a shaped area it is the step's length weighted by how
/// far the cell lies from the area's centre along each diagonal; otherwise the plain distance.
/// </summary>
double MapGeneratorClass::Direction_Weighted_Cell_Distance(Cell const & from, Cell const & to, Rect const & rect, Cell const & center, float weight_x, float weight_y)
{
	if (!(rect == RECT_NONE)) {
		int u = abs(((to.X - to.Y) >> 1) - ((center.X - center.Y) >> 1));
		int v = abs(((to.X + to.Y) >> 1) - ((center.X + center.Y) >> 1));
		if (u == 0 && v == 0) {
			static const float zero = 0.0f;
			return zero;
		}
		double length = fastmath::sqrt((double)(v * v + u * u));
		double ratio_u = u / length;
		double ratio_v = v / length;
		int x = from.X - to.X;
		int y = from.Y - to.Y;
		double steps = MAX(abs(x), abs(y));
		return (weight_x * ratio_u + ratio_v * weight_y) * steps;
	}
	int dx = from.X - to.X;
	int dy = from.Y - to.Y;
	return fastmath::sqrt((double)(dy * dy + dx * dx));
}
