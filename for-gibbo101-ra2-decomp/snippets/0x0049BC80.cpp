// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0049BC80 (26 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x8e490 (VA 0x0048E490, 32 bytes incl. padding)
// RA2 symbol : ?Get_Campaign_Type@CoopCampaignClass@@QAE_NPAH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7692)
// source TU  : src/ra2/coopcamp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x48e490
bool CoopCampaignClass::Get_Campaign_Type(int * type)
{
    if (!IsActive) return false;
    *type = CampaignType;
    return true;
}
