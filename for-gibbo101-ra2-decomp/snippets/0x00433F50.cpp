// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00433F50 (331 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x315d0 (VA 0x004315D0, 336 bytes incl. padding)
// RA2 symbol : ?Chars_In_Width@BitFont@@QAEHPBGHHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9811)
// source TU  : src/m85/src/bitfont.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/*
**	The number of characters of text that fit in maxwidth, at most maxchars (0: no
**	limit). With wrap, a line break ends the count and a word that does not fit is left out.
*/
int BitFont::Chars_In_Width(wchar_t const * text, int maxwidth, int maxchars, int wrap)
{
	int width = 0;
	int count = 0;
	if (!Data || !text) return 0;
	{
		unsigned short ch = *text;
		while (ch) {
			switch (ch) {
				case 9:
					width += TabWidth;
					width -= width % TabWidth;
					break;
				case 10:
				case 13:
					break;
				default: {
					unsigned char * bitmap = Char_Data(ch);
					if (!bitmap) bitmap = (unsigned char *)MissingChar;
					if (bitmap) width += *bitmap + Spacing;
					break;
				}
			}
			++count;
			if (width > maxwidth) {
				--count;
				if (wrap && ch > 32) {
					--text;
					int split = count;
					while (split && *text > 32) {
						--split;
						--text;
					}
					if (split) count = split;
				}
				break;
			}
			if (maxchars && count == maxchars) break;
			if (wrap && (ch == 13 || ch == 10)) break;
			ch = *++text;
		}
	}
	return count;
}
