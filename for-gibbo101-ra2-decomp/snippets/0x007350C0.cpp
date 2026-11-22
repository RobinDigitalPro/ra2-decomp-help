// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007350C0 (88 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2eedc0 (VA 0x006EEDC0, 96 bytes incl. padding)
// RA2 symbol : ?Wide_To_Narrow@@YIPADPBG@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8919)
// source TU  : src/m85/src/strtable.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// A wide string narrowed into one of eight static buffers of 1024 bytes, used in turn; NULL for NULL.
/// </summary>
char * __fastcall Wide_To_Narrow(wchar_t const * text) // RA2: 0x006FA120
{
	if (!text) { // RA2: as above
		return 0; // RA2: as above
	}
	char * buffer = NarrowBuffers[NarrowIndex]; // RA2: as above
	OwnerDraw::WideToCharString(buffer, text, 0x400); // RA2: as above
	buffer[0x3FF] = 0; // RA2: as above
	NarrowIndex = (NarrowIndex + 1) & 7; // RA2: the next call uses the next buffer
	return buffer; // RA2: as above
}
