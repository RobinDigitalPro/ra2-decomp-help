// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004C2790 (155 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xb1e80 (VA 0x004B1E80, 160 bytes incl. padding)
// RA2 symbol : ?Draw@EBolt@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9580)
// source TU  : src/m85/src/ebolt.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Draws the bolt when it crosses the visible part of the tactical view, then halves its lifetime.
/// </summary>
void EBolt::Draw(void) // RA2: 0x004B2170
{
	if (Lifetime != 0) { // RA2: as above
		Point2D p1; // RA2: as above
		Point2D p2; // RA2: as above
		TacticalMap->Coord_To_Pixel(Point1, p1); // RA2: as above
		TacticalMap->Coord_To_Pixel(Point2, p2); // RA2: as above
		if (Clip_Line_To_Rect(p1, p2, TacticalRect)) { // RA2: as above
			Draw_Bolt(Point1, Point2, AlternateColor ? 5 : 10); // RA2: as above
		} // RA2: as above
		Random++; // RA2: as above
	} // RA2: as above
	Lifetime >>= 1; // RA2: as above
}
