// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004E3320 (96 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xd0a80 (VA 0x004D0A80, 96 bytes incl. padding)
// RA2 symbol : ?Player_Flag_ID@@YIHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/ra2/GDlgSupp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int Player_Flag_ID(int slot)
{
    if (slot == 0) return 0x6DA;
    if (slot == 1) return 0x6DB;
    if (slot == 2) return 0x6DC;
    if (slot == 3) return 0x6DD;
    if (slot == 4) return 0x6DE;
    if (slot == 5) return 0x6DF;
    if (slot == 6) return 0x6E0;
    if (slot == 7) return 0x6E1;
    return -1;
}
