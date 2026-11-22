// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0049D0F0 (35 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x8f9a0 (VA 0x0048F9A0, 48 bytes incl. padding)
// RA2 symbol : ?Get_Player2@CoopCampaignClass@@QAE_NPAH0@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6667)
// source TU  : src/ra2/coopcamp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x48f9a0
bool CoopCampaignClass::Get_Player2(int * house, int * color)
{
    if (IsActive) {
        *house = Players[1].House;
        *color = Players[1].Color;
        return true;
    }
    return false;
}
