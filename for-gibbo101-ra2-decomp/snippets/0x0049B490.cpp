// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0049B490 (165 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x8dca0 (VA 0x0048DCA0, 176 bytes incl. padding)
// RA2 symbol : ?Quoted_Printable_Encode@@YIPADPBD@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9134)
// source TU  : src/m85/src/coopcamp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Turns a name into letters and digits only (everything else becomes =XX), so that it can be part of an
/// INI section name. The result is in a static buffer.
/// </summary>
char * __fastcall Quoted_Printable_Encode(char const * input) // RA2: 0x0048DEC0
{
	char const * cursor = input; // RA2: as above
	int length; // RA2: as above
	for (length = 0; *cursor && length < 1021; ++length, ++cursor) { // RA2: stops at 1021 so that the three characters of a =XX still fit the 1024 character buffer at 0x00851170
		if (!isalnum(*cursor)) { // RA2: everything but letters and digits is written as = and two hexadecimal digits
			EncodedBuffer[length] = '='; // RA2: the escape mark
			++length; // RA2: as above
			EncodedBuffer[length] = Hex_Digit(*cursor >> 4); // RA2: the high nibble of the (signed) character
			++length; // RA2: as above
			EncodedBuffer[length] = Hex_Digit(*cursor & 15); // RA2: the low nibble
		} else {
			EncodedBuffer[length] = *cursor; // RA2: letters and digits are copied
		}
	}
	EncodedBuffer[length] = 0; // RA2: as above
	return(EncodedBuffer); // RA2: as above
}
