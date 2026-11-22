// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0049D070 (74 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x8f920 (VA 0x0048F920, 80 bytes incl. padding)
// RA2 symbol : ?Get_Map@CoopCampaignClass@@QAE_NPAPADH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9118)
// source TU  : src/ra2/coopcamp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x48f920
bool CoopCampaignClass::Get_Map(char ** map, int index)
{
    bool result = false;
    *map = NULL;
    if (index == -1) {
        index = CurrentMap;
    }
    if (index < 0 || index >= MapCount) {
        index = -1;
    }
    if (IsActive) {
        if (index != -1) {
            *map = Maps[index];
        }
        if (*map != NULL) {
            result = true;
        }
    }
    return result;
}
