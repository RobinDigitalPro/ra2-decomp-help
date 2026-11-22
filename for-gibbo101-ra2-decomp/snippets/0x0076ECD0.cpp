// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0076ECD0 (62 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x324b40 (VA 0x00724B40, 64 bytes incl. padding)
// RA2 symbol : ?Func_724B40@@YIXABV?$rc_ptr@VCampaign@WorldDominationTour@@@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9524)
// source TU  : src/ra2/WDTSel.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x324b40
void Func_724B40(rc_ptr<WorldDominationTour::Campaign> const & campaign, int theater)
{
    Keyboard->Clear();
    Selection selection(campaign, theater);
    selection.Play_Summary(theater);
}
