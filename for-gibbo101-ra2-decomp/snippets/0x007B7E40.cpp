// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007B7E40 (135 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x35ca70 (VA 0x0075CA70, 144 bytes incl. padding)
// RA2 symbol : ?Int_To_WideString_Width@@YI?AVWideWstring@@HH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9159)
// source TU  : src/m85/src/wstring.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: Builds a wide string from an integer, zero padded to the width.
/// </summary>
WideWstring __fastcall Int_To_WideString_Width(int value, int width) // RA2: as above
{
	wchar_t buf[32]; // RA2: as above
	swprintf(buf, L"%%0%dd", width); // RA2: as above
	swprintf(buf, buf, value); // RA2: as above
	return(WideWstring(buf)); // RA2: as above
}
