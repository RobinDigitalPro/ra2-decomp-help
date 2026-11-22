// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00767460 (120 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31d390 (VA 0x0071D390, 128 bytes incl. padding)
// RA2 symbol : ?Create@FlagGameOption@WorldDominationTour@@SI?AV?$rc_ptr@VFlagGameOption@WorldDominationTour@@@@HVCharStringClass@@H0H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9200)
// source TU  : src/ra2/WDTGameOptions.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x31d390
rc_ptr<FlagGameOption> FlagGameOption::Create(int mask, CharStringClass clear_label, int clear_status, CharStringClass set_label, int set_status)
{
    return rc_ptr<FlagGameOption>(new FlagGameOption(mask, clear_label, clear_status, set_label, set_status));
}
