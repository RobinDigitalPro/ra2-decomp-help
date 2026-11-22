// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00769440 (59 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31f330 (VA 0x0071F330, 64 bytes incl. padding)
// RA2 symbol : ?Is_Over_Back@Map@WorldDominationTour@@QBEHABVPoint2D@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9123)
// source TU  : src/m85/src/wdtmap.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: whether a point is inside the back button's rectangle.
/// </summary>
int Map::Is_Over_Back(Point2D const & point) const // RA2: whether a point is inside the back button's rectangle
{
	if (point.X >= BackButtonRect.X && point.X < BackButtonRect.Width + BackButtonRect.X) { // RA2: as above
		if (point.Y >= BackButtonRect.Y && point.Y < BackButtonRect.Height + BackButtonRect.Y) { // RA2: as above
			return 1; // RA2: as above
		}
	}
	return 0; // RA2: as above
}
