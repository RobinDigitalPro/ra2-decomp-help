// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0058BD40 (19 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x16a430 (VA 0x0056A430, 32 bytes incl. padding)
// RA2 symbol : ?Is_Mountain_Or_Inland_Map@@YI_NH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5517)
// source TU  : src/m85/src/mapgen.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool Is_Mountain_Or_Inland_Map(int map_type)
{
	return map_type == 4 || map_type == 3;
}
