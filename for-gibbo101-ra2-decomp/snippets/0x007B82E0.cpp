// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007B82E0 (251 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x35cf10 (VA 0x0075CF10, 256 bytes incl. padding)
// RA2 symbol : ?Wstring_FromWide@@YI?AVWstring@@ABVWideWstring@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9767)
// source TU  : src/m85/src/wstring.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: Packs the 16 bit characters into a string of 7 bit characters (Bit_Stuff).
/// </summary>
Wstring __fastcall Wstring_FromWide(WideWstring const& wide) // RA2: as above
{
	int bits = (wide.length() + 1) * 16; // RA2: as above
	unsigned char* buffer = new unsigned char[(bits + 6) / 7]; // RA2: as above
	Bit_Stuff((unsigned char*)wide.get(), buffer, bits); // RA2: as above
	Wstring packed((char*)buffer); // RA2: as above
	delete(buffer); // RA2: as above
	return(packed); // RA2: as above
}
