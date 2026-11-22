// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00732CA0 (28 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2ec490 (VA 0x006EC490, 32 bytes incl. padding)
// RA2 symbol : ?Type_Select_Key_Down@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7778)
// source TU  : src/ra2/UICmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x2ec490
void Type_Select_Key_Down()
{
    if (!TypeSelectDown) {
        TypeSelectDown = true;
        TypeSelectTime = timeGetTime();
    }
}
