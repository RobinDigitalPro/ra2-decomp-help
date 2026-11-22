// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007B7DD0 (109 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x35ca00 (VA 0x0075CA00, 112 bytes incl. padding)
// RA2 symbol : ?WideWstring_FromInt@@YI?AVWideWstring@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9630)
// source TU  : src/m85/src/wstring.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: Builds a wide string from an integer.
/// </summary>
WideWstring __fastcall WideWstring_FromInt(int value) // RA2: as above
{
	wchar_t buf[32]; // RA2: as above
	swprintf(buf, L"%d", value); // RA2: as above
	return(WideWstring(buf)); // RA2: as above
}
