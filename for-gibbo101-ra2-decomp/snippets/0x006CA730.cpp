// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006CA730 (120 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x291590 (VA 0x00691590, 128 bytes incl. padding)
// RA2 symbol : ?Parse_Color@@YIXPAGPAVSubTitle@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9216)
// source TU  : src/m85/src/subtitle2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: Color=: red:green:blue.
/// </summary>
void __fastcall Parse_Color(wchar_t * value, SubTitle * subtitle) // RA2: 0x0069BEF0
{
	wchar_t * colon = wcschr(value, L':'); // RA2: as above
	*colon = 0; // RA2: as above
	unsigned char red = (unsigned char)wcstoul(value, NULL, 10); // RA2: as above

	wchar_t * next = colon + 1; // RA2: as above
	colon = wcschr(next, L':'); // RA2: as above
	*colon = 0; // RA2: as above
	unsigned char green = (unsigned char)wcstoul(next, NULL, 10); // RA2: as above

	unsigned char blue = (unsigned char)wcstoul(colon + 1, NULL, 10); // RA2: as above

	subtitle->Set_RGB_Color(red, green, blue); // RA2: as above
}
