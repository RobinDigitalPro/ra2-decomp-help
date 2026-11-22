// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0065D690 (5 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31d240 (VA 0x0071D240, 16 bytes incl. padding)
// RA2 symbol : ?Is_Fixed@GameOption@WorldDominationTour@@QBE_NABV?$rc_ptr@VWDTTerritory@@@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.2667)
// source TU  : src/ra2/WDTGameOptions.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x31d240
bool GameOption::Is_Fixed(rc_ptr<WDTTerritory> const &) const
{
    return false;
}
