// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006ACBC0 (92 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x277f80 (VA 0x00677F80, 96 bytes incl. padding)
// RA2 symbol : ?AI_Combo_Index@@YIHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9394)
// source TU  : src/ra2/Skirmish.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int AI_Combo_Index(int id)
{
    if (id == 0x50B) return 0;
    if (id == 0x50E) return 1;
    if (id == 0x516) return 2;
    if (id == 0x51A) return 3;
    if (id == 0x51B) return 4;
    if (id == 0x51C) return 5;
    if (id == 0x51D) return 6;
    return -1;
}
