// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00735120 (96 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2eee20 (VA 0x006EEE20, 96 bytes incl. padding)
// RA2 symbol : ?Narrow_To_Wide@@YIPAGPBD@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/strtable.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// A narrow string widened into one of eight static buffers of 1024 characters, used in turn; NULL for NULL.
/// </summary>
wchar_t * __fastcall Narrow_To_Wide(char const * narrow) // RA2: 0x006FA180
{
	if (!narrow) { // RA2: as above
		return 0; // RA2: as above
	}
	wchar_t * buffer = WideBuffers[WideIndex]; // RA2: as above
	Char_To_Wide(buffer, narrow, 0x400); // RA2: as above
	buffer[0x3FF] = 0; // RA2: as above
	WideIndex = (WideIndex + 1) & 7; // RA2: the next call uses the next buffer
	return buffer; // RA2: as above
}
