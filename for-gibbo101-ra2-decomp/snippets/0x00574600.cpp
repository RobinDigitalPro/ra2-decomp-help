// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00574600 (187 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x153fc0 (VA 0x00553FC0, 192 bytes incl. padding)
// RA2 symbol : ?Is_Bridge_Span_End@@YI_NHHPBVCellClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9645)
// source TU  : src/m85/src/map.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Is_Bridge_Span_End(int tile, int kind, CellClass const *cell) // RA2: RA2's form
{
	if (kind == 2) { // RA2: as above
		if (tile == IsometricTileTypeClass::BridgeBottomRight1 && cell->SubTile == 4) { // RA2: as above
			return(true);
		}
		if (tile == IsometricTileTypeClass::BridgeBottomRight2 && cell->SubTile == 4) { // RA2: as above
			return(true);
		}
		if ((tile == IsometricTileTypeClass::BridgeMiddle1 || tile == IsometricTileTypeClass::BridgeMiddle1 + 3 // RA2: as above
				|| tile == IsometricTileTypeClass::BridgeMiddle1 + 1 || tile == IsometricTileTypeClass::BridgeMiddle1 + 2) // RA2: as above
				&& cell->SubTile == 4) { // RA2: as above
			return(true);
		}
	} else if (kind == 4) { // RA2: as above
		if (tile == IsometricTileTypeClass::BridgeBottomLeft1 && cell->SubTile == 2) { // RA2: as above
			return(true);
		}
		if (tile == IsometricTileTypeClass::BridgeBottomLeft2 && cell->SubTile == 2) { // RA2: as above
			return(true);
		}
		if ((tile == IsometricTileTypeClass::BridgeMiddle2 || tile == IsometricTileTypeClass::BridgeMiddle2 + 3 // RA2: as above
				|| tile == IsometricTileTypeClass::BridgeMiddle2 + 1 || tile == IsometricTileTypeClass::BridgeMiddle2 + 2) // RA2: as above
				&& cell->SubTile == 2) { // RA2: as above
			return(true);
		}
	}
	return(false);
}
