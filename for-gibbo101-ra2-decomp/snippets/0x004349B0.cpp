// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004349B0 (60 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x32030 (VA 0x00432030, 64 bytes incl. padding)
// RA2 symbol : ?Get_Char_Width@BitFont@@QAEHG@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9200)
// source TU  : src/ra2/unnamed/BitFont.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x432030
int BitFont::Get_Char_Width(wchar_t c)
{
    unsigned char const * data = Char_Data(c);
    if (data) {
        return *data;
    }
    return 0;
}
