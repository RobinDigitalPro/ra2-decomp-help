// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0076F910 (82 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x325740 (VA 0x00725740, 96 bytes incl. padding)
// RA2 symbol : ?Create@Territory@WorldDominationTour@@SI?AV?$rc_ptr@VTerritory@WorldDominationTour@@@@HAAVINIClass@@ABVCharStringClass@@11@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8250)
// source TU  : src/ra2/WDTTerr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x325740
rc_ptr<Territory> Territory::Create(int id, INIClass & ini, CharStringClass const & section,
    CharStringClass const & shape_prefix, CharStringClass const & name_prefix)
{
    return rc_ptr<Territory>(new Territory(id, ini, section, shape_prefix, name_prefix));
}
