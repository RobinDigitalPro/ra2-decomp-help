// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005C26D0 (59 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1a0650 (VA 0x005A0650, 64 bytes incl. padding)
// RA2 symbol : ?Init_Coop_Player_Colors@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8889)
// source TU  : src/ra2/MPCoop.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x1a0650
void Init_Coop_Player_Colors()
{
    for (int index = 0; index < 8; index++) {
        PlayerColors[index] = -2;
    }
    int count = Session.Players.Count();
    for (index = 0; index < count; index++) {
        PlayerColors[index] = Session.Players[index]->Get_Color();
    }
}
