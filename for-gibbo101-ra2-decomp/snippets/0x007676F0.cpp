// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007676F0 (68 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31d620 (VA 0x0071D620, 80 bytes incl. padding)
// RA2 symbol : ?Create@MapSizeGameOption@WorldDominationTour@@SI?AV?$rc_ptr@VMapSizeGameOption@WorldDominationTour@@@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8065)
// source TU  : src/ra2/WDTGameOptions.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x31d620
rc_ptr<MapSizeGameOption> MapSizeGameOption::Create(int mask)
{
    return rc_ptr<MapSizeGameOption>(new MapSizeGameOption(mask));
}
