// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006ACB60 (85 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x277f20 (VA 0x00677F20, 96 bytes incl. padding)
// RA2 symbol : ?AI_Combo_ID@@YIHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8493)
// source TU  : src/ra2/Skirmish.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// Combo box of the AI player in slot index + 1.
int AI_Combo_ID(int index)
{
    if (index == 0) return 0x50B;
    if (index == 1) return 0x50E;
    if (index == 2) return 0x516;
    if (index == 3) return 0x51A;
    if (index == 4) return 0x51B;
    if (index == 5) return 0x51C;
    if (index == 6) return 0x51D;
    return -1;
}
