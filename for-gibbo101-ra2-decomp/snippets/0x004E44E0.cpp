// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004E44E0 (145 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xd1800 (VA 0x004D1800, 160 bytes incl. padding)
// RA2 symbol : ?Combo_Color@@YIHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8515)
// source TU  : src/ra2/GDlgSupp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int Combo_Color(int id)
{
    int slot = Player_Color_Slot(id);
    for (int color = 0; color < MAX_COLORS; color++) {
        if (PlayerColors[color].Owner == slot) {
            return color;
        }
    }
    return -1;
}
