// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00574780 (572 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x154080 (VA 0x00554080, 576 bytes incl. padding)
// RA2 symbol : ?Destroy_Low_Bridge_Span@MapClass@@AAEXABVCell@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9891)
// source TU  : src/m85/src/map.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void MapClass::Destroy_Low_Bridge_Span(Cell const &cell) // RA2: RA2's form
{
	int overlay = Map[cell].Overlay; // RA2: as above

	if (overlay >= 0x4a && overlay <= 0x52 || overlay >= 0x5c && overlay <= 0x5f || overlay == 0x64) { // RA2: as above
		if (!Is_Low_Bridge(cell - Cell(0, 1))) {
			Destroy_Low_Bridge_EW(cell + Cell(0, 1)); // RA2: as above
		} else {
			if (!Is_Low_Bridge(cell - Cell(0, 2))) {
				Destroy_Low_Bridge_EW(cell); // RA2: as above
			} else {
				Destroy_Low_Bridge_EW(cell - Cell(0, 1)); // RA2: as above
			}
		}
	} else if (overlay >= 0x53 && overlay <= 0x5b || overlay >= 0x60 && overlay <= 0x63 || overlay == 0x65) { // RA2: as above
		if (!Is_Low_Bridge(cell - Cell(1, 0))) {
			Destroy_Low_Bridge_NS(cell + Cell(1, 0)); // RA2: as above
		} else {
			if (!Is_Low_Bridge(cell - Cell(2, 0))) {
				Destroy_Low_Bridge_NS(cell); // RA2: as above
			} else {
				Destroy_Low_Bridge_NS(cell - Cell(1, 0)); // RA2: as above
			}
		}
	}
}
