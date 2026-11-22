// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005749C0 (608 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1542c0 (VA 0x005542C0, 608 bytes incl. padding)
// RA2 symbol : ?Destroy_Low_Bridge2_Span@MapClass@@AAEXABVCell@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/map.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void MapClass::Destroy_Low_Bridge2_Span(Cell const &cell) // RA2: RA2's form
{
	int overlay = Map[cell].Overlay; // RA2: as above

	if (overlay >= 0xcd && overlay <= 0xd5 || overlay >= 0xdf && overlay <= 0xe2 || overlay == 0xe7) { // RA2: as above
		if (!Is_Low_Bridge2(cell - Cell(0, 1))) { // RA2: as above
			Destroy_Low_Bridge2_EW(cell + Cell(0, 1)); // RA2: as above
		} else {
			if (!Is_Low_Bridge2(cell - Cell(0, 2))) { // RA2: as above
				Destroy_Low_Bridge2_EW(cell); // RA2: as above
			} else {
				Destroy_Low_Bridge2_EW(cell - Cell(0, 1)); // RA2: as above
			}
		}
	} else if (overlay >= 0xd6 && overlay <= 0xde || overlay >= 0xe3 && overlay <= 0xe6 || overlay == 0xe8) { // RA2: as above
		if (!Is_Low_Bridge2(cell - Cell(1, 0))) { // RA2: as above
			Destroy_Low_Bridge2_NS(cell + Cell(1, 0)); // RA2: as above
		} else {
			if (!Is_Low_Bridge2(cell - Cell(2, 0))) { // RA2: as above
				Destroy_Low_Bridge2_NS(cell); // RA2: as above
			} else {
				Destroy_Low_Bridge2_NS(cell - Cell(1, 0)); // RA2: as above
			}
		}
	}
}
