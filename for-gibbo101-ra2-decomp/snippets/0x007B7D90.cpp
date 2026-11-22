// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007B7D90 (49 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x35c9c0 (VA 0x0075C9C0, 64 bytes incl. padding)
// RA2 symbol : ?Is_Narrow@WideWstring@@QBE_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7619)
// source TU  : src/m85/src/wstring.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: Checks whether every character is below 0x100 (true for no text).
/// </summary>
bool WideWstring::Is_Narrow(void) const // RA2: as above
{
	if (str != NULL) // RA2: as above
	{
		int len = wcslen(str); // RA2: as above
		for (int i = 0; i < len; i++) // RA2: as above
		{
			if (str[i] >= 0x100) // RA2: as above
				return(false); // RA2: as above
		}
	}
	return(true); // RA2: as above
}
