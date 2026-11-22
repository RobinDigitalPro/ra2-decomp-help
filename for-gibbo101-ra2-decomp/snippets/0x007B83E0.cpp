// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007B83E0 (201 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x35d010 (VA 0x0075D010, 208 bytes incl. padding)
// RA2 symbol : ?Wide_From_7_Bit@@YI?AVWideWstring@@ABVWstring@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9591)
// source TU  : src/m85/src/wstring.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: Unpacks a string of 7 bit characters into 16 bit characters (Bit_Unstuff_String).
/// </summary>
WideWstring __fastcall Wide_From_7_Bit(Wstring const& string) // RA2: as above
{
	int bytes = (string.length() + 1) * 7 / 8; // RA2: as above
	int count = (bytes + 1) / 2; // RA2: as above
	wchar_t* buffer = new wchar_t[count + 1]; // RA2: as above
	Bit_Unstuff_String((unsigned char*)string.get(), buffer, count); // RA2: as above
	WideWstring wide(buffer); // RA2: as above
	delete(buffer); // RA2: as above
	return(wide); // RA2: as above
}
