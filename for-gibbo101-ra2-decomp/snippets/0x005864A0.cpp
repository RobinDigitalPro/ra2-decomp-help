// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005864A0 (309 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x165070 (VA 0x00565070, 320 bytes incl. padding)
// RA2 symbol : ?Is_Under_Fog@MapClass@@QAE_NABVCoord@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9469)
// source TU  : src/m85/src/map.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool MapClass::Is_Under_Fog(Coord const & coord) // RA2: 0x568280, is the coordinate under fog for the player (checks the allied gap coverage)
{
	int level = coord.Z / LEVEL_LEPTON_H; // RA2: as above
	if ((level & 1) != 0) { // RA2: as above
		int offset = level / 2 + 1; // RA2: as above
		Cell cell = Cell(coord.X / 256, coord.Y / 256); // RA2: as above
		CellClass *cellptr = &Map[Cell(cell.X - offset, cell.Y - offset)]; // RA2: as above
		if ((int)cellptr->AlliedGapsCoveringThisCell <= 0) { // RA2: as above
			return(false); // RA2: as above
		}
		if ((int)cellptr->Adjacent_Cell(FACING_SE).AlliedGapsCoveringThisCell > 0) { // RA2: as above
			return(true); // RA2: as above
		}
	} else { // RA2: as above
		int offset = level / 2; // RA2: as above
		Cell cell = Cell(coord.X / 256, coord.Y / 256); // RA2: as above
		CellClass *cellptr = &Map[Cell(cell.X - offset, cell.Y - offset)]; // RA2: as above
		if ((int)cellptr->AlliedGapsCoveringThisCell > 0) { // RA2: as above
			return(true); // RA2: as above
		}
	}
	return(false); // RA2: as above
}
