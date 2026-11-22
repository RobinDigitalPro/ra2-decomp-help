// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004E3380 (105 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xd0ae0 (VA 0x004D0AE0, 112 bytes incl. padding)
// RA2 symbol : ?Player_Flag_Slot@@YIHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9091)
// source TU  : src/ra2/GDlgSupp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int Player_Flag_Slot(int id)
{
    if (id == 0x6DA) return 0;
    if (id == 0x6DB) return 1;
    if (id == 0x6DC) return 2;
    if (id == 0x6DD) return 3;
    if (id == 0x6DE) return 4;
    if (id == 0x6DF) return 5;
    if (id == 0x6E0) return 6;
    if (id == 0x6E1) return 7;
    return -1;
}
