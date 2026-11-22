// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0046D490 (7 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x65be0 (VA 0x00465BE0, 16 bytes incl. padding)
// RA2 symbol : ?Get_Flag@CampaignScoreClass@@SI_NH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.3077)
// source TU  : src/ra2/CampScor.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x465be0
bool CampaignScoreClass::Get_Flag(int index)
{
    return CampaignFlags[index];
}
