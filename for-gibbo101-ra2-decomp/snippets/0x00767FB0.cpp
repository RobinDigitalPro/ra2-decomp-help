// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00767FB0 (75 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31dea0 (VA 0x0071DEA0, 80 bytes incl. padding)
// RA2 symbol : ?Create@Map@WorldDominationTour@@SI?AV?$rc_ptr@VMap@WorldDominationTour@@@@HHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9206)
// source TU  : src/m85/src/wdtmap.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: a new map, counted.
/// </summary>
rc_ptr<Map> __fastcall Map::Create(int map, int faction, int player_faction) // RA2: a new map, counted
{
	return rc_ptr<Map>(new Map(map, faction, player_faction)); // RA2: as above
}
