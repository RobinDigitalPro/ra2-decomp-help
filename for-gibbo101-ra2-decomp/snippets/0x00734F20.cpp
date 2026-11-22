// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00734F20 (44 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2eec20 (VA 0x006EEC20, 48 bytes incl. padding)
// RA2 symbol : ?Is_Language_English@@YIHXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8824)
// source TU  : src/m85/src/strtable.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// True when the language read is one whose strings are English (or has no code letter).
/// </summary>
int __fastcall Is_Language_English(void) // RA2: 0x006F9F80
{
	char const * letter = Languages[StringLanguage].Letter; // RA2: the table is indexed by the language directly
	if (letter == 0) { // RA2: as above
		return 1; // RA2: as above
	}
	return stricmp(letter, "e") == 0; // RA2: the literal at 0x007F8E34, shared with the table
}
