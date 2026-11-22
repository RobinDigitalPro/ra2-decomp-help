// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0058BCD0 (24 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x16a3c0 (VA 0x0056A3C0, 32 bytes incl. padding)
// RA2 symbol : ?Is_Map_Type_1_3_Or_4@@YI_NH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7143)
// source TU  : src/m85/src/mapgen.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// level-2 1.001: six out-of-line map-type predicates (0x56A3C0..0x56A470). Nothing calls them in
// 1.001 (the callers test the map type inline); their bodies follow gibbo101's YR mapgen.cpp.
bool Is_Map_Type_1_3_Or_4(int map_type)
{
	return map_type == 1 || map_type == 3 || map_type == 4;
}
