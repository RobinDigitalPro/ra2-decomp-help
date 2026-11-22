// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00412A40 (116 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x127a0 (VA 0x004127A0, 128 bytes incl. padding)
// RA2 symbol : ?Shift_Bin@AircraftTrackerClass@@QAEHHVPoint2D@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8824)
// source TU  : src/m85/src/atracker.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Gives the bin an offset away from a bin on the 20 by 20 grid, kept inside the grid.
/// </summary>
int AircraftTrackerClass::Shift_Bin(int index, Point2D offset) // RA2: 0x004127A0
{
	int x = index % 20;
	int y = index / 20;
	x = MIN(19, MAX(0, x + offset.X)); // RA2: clamped to the grid
	y = MIN(19, MAX(0, y + offset.Y)); // RA2: as above
	return x + y * 20;
}
