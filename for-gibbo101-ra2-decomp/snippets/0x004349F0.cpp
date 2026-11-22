// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004349F0 (74 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x32070 (VA 0x00432070, 80 bytes incl. padding)
// RA2 symbol : ?Init@BitFont@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9000)
// source TU  : src/ra2/unnamed/BitFont.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x432070
void BitFont::Init()
{
    Header = NULL;
    Color = 0x7fff;
    Background = 0x3555;
    TabWidth = 64;
    IsBold = true;
    IsClipping = true;
    BytesPerRow = 1;
    LineHeight = 1;
    TabOrigin = 0;
    Buffer = NULL;
    Missing = NULL;
    SetRect(&Bounds, 0, 0, 0, 0);
    Spacing = 1;
}
