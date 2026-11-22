// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005889F0 (203 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1676f0 (VA 0x005676F0, 208 bytes incl. padding)
// RA2 symbol : ?Find_Compatible_Passability_Row@@YIHHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9645)
// source TU  : src/m85/src/map.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __fastcall Find_Compatible_Passability_Row(int row1, int row2) // RA2: 0x56A900, the zone layer (0-11) that is passable wherever both given layers are, with the most such columns; -1 if none
{
	int best = -1; // RA2: as above
	int best_count = 0; // RA2: as above
	for (int row = 0; row < 12; row++) { // RA2: as above
		bool ok = true; // RA2: as above
		int count = 0; // RA2: as above
		for (int index = 0; index < 8; index++) { // RA2: as above
			int value1 = MZonePassability[row1][index]; // RA2: as above
			int value2 = MZonePassability[row2][index]; // RA2: as above
			int value = MZonePassability[row][index]; // RA2: as above
			if ((value1 == 2 || value2 == 2) && value == 1) { // RA2: as above
				ok = false; // RA2: as above
			}
			if (value1 == value && value2 == value && value == 1) { // RA2: as above
				count++; // RA2: as above
			}
		}
		if (ok && count > best_count) { // RA2: as above
			best_count = count; // RA2: as above
			best = row; // RA2: as above
		}
	}
	return best; // RA2: as above
}
