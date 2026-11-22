// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00434500 (439 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31b80 (VA 0x00431B80, 448 bytes incl. padding)
// RA2 symbol : ?Print_Typed@BitFont@@QAEHPBGHHHH@Z
// similarity : 0.9925 (very-similar, masked instruction tokens; shape 0.9673)
// source TU  : src/m85/src/bitfont.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/*
**	Prints text, at most maxchars characters (0: all). With shown set, only that many
**	characters are drawn, the last eight brightened towards white, and the result is the x
**	the whole text would end at.
*/
int BitFont::Print_Typed(wchar_t const * text, int x, int y, int maxchars, int shown)
{
	int count = 0;
	unsigned short ch = *text++;
	unsigned short saved = Color;
	if (ch) {
		int t = shown - 1;
		int ratio = (9 - shown) * 31;
		while (ch) {
			if (shown) {
				if (count >= shown) {
					Color = saved;
					int width;
					Text_Dimensions(text, &width, 0, 0);
					return x + width;
				}
				if (t < 8) {
					unsigned char r = (saved >> DSurface::RedRight) << DSurface::RedLeft;
					unsigned char b = (saved >> DSurface::BlueRight) << DSurface::BlueLeft;
					unsigned char g = (saved >> DSurface::GreenRight) << DSurface::GreenLeft;
					RGBClass c = RGBClass(r, g, b);
					c.Adjust(ratio, WhiteColor);
					Color = (unsigned short)(((c.Get_Green() >> DSurface::GreenLeft) << DSurface::GreenRight)
						| ((c.Get_Blue() >> DSurface::BlueLeft) << DSurface::BlueRight)
						| ((c.Get_Red() >> DSurface::RedLeft) << DSurface::RedRight));
				}
				count++;
				ratio += 31;
				t--;
			}
			if (ch != 13 && ch != 10) {
				x = Print_Char(ch, x, y, -1);
			}
			if (maxchars && --maxchars == 0) break;
			ch = *text++;
		}
	}
	Color = saved;
	return x;
}
