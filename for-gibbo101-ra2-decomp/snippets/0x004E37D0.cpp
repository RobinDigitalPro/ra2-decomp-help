// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004E37D0 (96 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xd0d70 (VA 0x004D0D70, 96 bytes incl. padding)
// RA2 symbol : ?Player_Side_ID@@YIHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/ra2/GDlgSupp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int Player_Side_ID(int slot)
{
    if (slot == 0) return 0x6A1;
    if (slot == 1) return 0x510;
    if (slot == 2) return 0x513;
    if (slot == 3) return 0x51E;
    if (slot == 4) return 0x514;
    if (slot == 5) return 0x51F;
    if (slot == 6) return 0x520;
    if (slot == 7) return 0x521;
    return -1;
}
