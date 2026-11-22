// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00554280 (202 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x134f10 (VA 0x00534F10, 208 bytes incl. padding)
// RA2 symbol : ?Draw_Text@@YIXPBGPAVSurface@@ABURectangleStruct@@GH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9552)
// source TU  : src/ra2/LdPrgMgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Draw_Text(wchar_t const * text, Surface * surface, RectangleStruct const & rect, unsigned short pixel, int justify)
{
    RectangleStruct area(rect.X, rect.Y, rect.X + rect.Width, rect.Y + rect.Height);
    RGBClass rgb = Pixel_To_RGB(pixel);
    Print_Text(surface, text, area, TextFont, RGB_Value(rgb), justify, 0xc, 0, 0, 0);
}
