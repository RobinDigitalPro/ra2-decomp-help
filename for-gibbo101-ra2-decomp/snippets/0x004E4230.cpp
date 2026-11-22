// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004E4230 (105 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xd1590 (VA 0x004D1590, 112 bytes incl. padding)
// RA2 symbol : ?Player_Color_Slot@@YIHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9091)
// source TU  : src/ra2/GDlgSupp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int Player_Color_Slot(int id)
{
    if (id == 0x6A2) return 0;
    if (id == 0x522) return 1;
    if (id == 0x523) return 2;
    if (id == 0x524) return 3;
    if (id == 0x525) return 4;
    if (id == 0x526) return 5;
    if (id == 0x527) return 6;
    if (id == 0x528) return 7;
    return -1;
}
