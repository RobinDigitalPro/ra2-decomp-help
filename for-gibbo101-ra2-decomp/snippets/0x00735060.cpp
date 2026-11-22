// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00735060 (47 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2eed60 (VA 0x006EED60, 48 bytes incl. padding)
// RA2 symbol : ?Char_To_Wide@@YIXPAGPBDH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9756)
// source TU  : src/m85/src/strtable.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Widens a narrow string into dest, at most limit characters (-1 for no limit). The characters are not sign extended.
/// </summary>
void __fastcall Char_To_Wide(wchar_t * dest, char const * source, int limit) // RA2: 0x006FA0C0
{
	while (*source != 0 && limit != 0) { // RA2: as above
		*dest++ = (unsigned char)*source++; // RA2: as above
		if (limit != -1) { // RA2: -1 counts down no further
			limit--; // RA2: as above
		}
	}
	*dest = 0; // RA2: as above
}
