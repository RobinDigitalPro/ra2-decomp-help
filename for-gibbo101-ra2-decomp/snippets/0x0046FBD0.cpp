// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0046FBD0 (33 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x66670 (VA 0x00466670, 48 bytes incl. padding)
// RA2 symbol : ?Func_66670@CampaignScoreClass@@SI_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5714)
// source TU  : src/ra2/CampScor.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x466670
bool CampaignScoreClass::Func_66670()
{
    if (Session.Type == 3) return Func_5B6EF0();
    if (Session.Type == 4) return Func_732A40();
    Call_Back();
    return false;
}
