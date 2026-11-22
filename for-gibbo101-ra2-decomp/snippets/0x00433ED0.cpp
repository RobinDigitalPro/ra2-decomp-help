// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00433ED0 (29 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31550 (VA 0x00431550, 32 bytes incl. padding)
// RA2 symbol : ?String_Pixel_Width@BitFont@@QAEHPBGH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8696)
// source TU  : src/ra2/unnamed/BitFont.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x431550
int BitFont::String_Pixel_Width(wchar_t const * text, int maxwidth)
{
    int width;
    String_Pixel_Rect(text, &width, NULL, maxwidth);
    return width;
}
