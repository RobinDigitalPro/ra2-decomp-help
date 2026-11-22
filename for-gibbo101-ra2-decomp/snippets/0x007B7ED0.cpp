// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007B7ED0 (182 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x35cb00 (VA 0x0075CB00, 192 bytes incl. padding)
// RA2 symbol : ?Wstring_ToWide@@YI?AVWideWstring@@ABVWstring@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9367)
// source TU  : src/m85/src/wstring.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: Widens a narrow string: the text goes through a scratch buffer into the result.
/// </summary>
WideWstring __fastcall Wstring_ToWide(Wstring const& string) // RA2: as above
{
	int len = string.length(); // RA2: as above
	wchar_t* buffer = new wchar_t[len + 1]; // RA2: as above
	Char_To_Wide(buffer, string.get(), len); // RA2: as above
	WideWstring wide(buffer); // RA2: as above
	delete(buffer); // RA2: as above
	return(wide); // RA2: as above
}
