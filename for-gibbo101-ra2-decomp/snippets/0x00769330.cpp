// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00769330 (106 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31f220 (VA 0x0071F220, 112 bytes incl. padding)
// RA2 symbol : ?Territory_At@Map@WorldDominationTour@@QBEHABVPoint2D@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9286)
// source TU  : src/m85/src/wdtmap.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: the number the click map holds under a screen point, -1 outside it.
/// </summary>
int Map::Territory_At(Point2D const & point) const // RA2: the number the click map holds under a screen point, -1 outside it
{
	Point2D local = point; // RA2: as above
	local.X -= Origin.X; // RA2: as above
	local.Y -= Origin.Y; // RA2: as above
	if (local.X >= 0 && local.X < ClickMap->Get_Width() && local.Y >= 0 && local.Y < ClickMap->Get_Height()) { // RA2: as above
		return ClickMap->Get_Pixel(local); // RA2: as above
	}
	return -1; // RA2: as above
}
