// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005541C0 (177 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x134e50 (VA 0x00534E50, 192 bytes incl. padding)
// RA2 symbol : ?Draw_Text_Box@@YIXPBGPAVSurface@@HHHH_N@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8872)
// source TU  : src/ra2/LdPrgMgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Draw_Text_Box(wchar_t const * text, Surface * surface, int x, int y, int width, int justify, bool full_width)
{
    RectangleStruct rect;
    int w = 0;
    int h = 0;
    TextFont->Get_Text_Size(text, &w, &h, width);
    if (full_width) {
        w = width;
    }
    rect = RectangleStruct(x, y, w, h);
    if (justify & 1) {
        rect.X = x + (width - w) / 2;
    } else if (justify & 2) {
        rect.X = x - w + width;
    }
    Inflate_Rect(rect, -4);
    Draw_Score_Frame(rect, surface, 0, 0x9f);
}
