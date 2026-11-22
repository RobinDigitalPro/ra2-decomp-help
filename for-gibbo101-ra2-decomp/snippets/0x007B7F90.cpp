// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007B7F90 (241 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x35cbc0 (VA 0x0075CBC0, 256 bytes incl. padding)
// RA2 symbol : ?Wstring_Narrow@@YI?AVWstring@@ABVWideWstring@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9339)
// source TU  : src/m85/src/wstring.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: Narrows a wide string: the text goes through a scratch buffer into the result.
/// </summary>
Wstring __fastcall Wstring_Narrow(WideWstring const& wide) // RA2: as above
{
	int len = wide.length(); // RA2: as above
	char* buffer = new char[len + 1]; // RA2: as above
	OwnerDraw::WideToCharString(buffer, wide.get(), len); // RA2: as above
	Wstring narrow(buffer); // RA2: as above
	delete(buffer); // RA2: as above
	return(narrow); // RA2: as above
}
