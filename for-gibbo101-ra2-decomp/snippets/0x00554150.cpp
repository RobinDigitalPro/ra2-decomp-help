// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00554150 (108 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x134de0 (VA 0x00534DE0, 112 bytes incl. padding)
// RA2 symbol : ?Loading_Rect@@YI?AURectangleStruct@@XZ
// similarity : 0.9500 (very-similar, masked instruction tokens; shape 0.9524)
// source TU  : src/ra2/LdPrgMgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

RectangleStruct Loading_Rect()
{
    RectangleStruct rect;
    if (ScreenWidth == LoadScreenWidths[0]) {
        rect = RectangleStruct(0x10, 0xeb, 200, 20);
    } else {
        rect = RectangleStruct(0x14, 0x12c, 200, 20);
    }
    if (ScreenWidth >= LoadScreenWidths[1]) {
        rect.X += (ScreenWidth - LoadScreenWidths[1]) / 2;
        rect.Y += (ScreenHeight - LoadScreenHeights[1]) / 2;
    }
    return rect;
}
