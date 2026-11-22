// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00734E30 (34 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2eeb30 (VA 0x006EEB30, 48 bytes incl. padding)
// RA2 symbol : ?Is_Narrow_Text@@YIHPBG@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6500)
// source TU  : src/m85/src/strtable.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// True when every character of a wide string fits one byte.
/// </summary>
int __fastcall Is_Narrow_Text(wchar_t const * text) // RA2: 0x006F9E90
{
	while (*text) { // RA2: as above
		if (*text++ > 0xFF) { // RA2: as above
			return 0; // RA2: as above
		}
	}
	return 1; // RA2: as above
}
