// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0058BCF0 (37 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x16a3e0 (VA 0x0056A3E0, 48 bytes incl. padding)
// RA2 symbol : ?Is_Not_Inland_Or_Mountain_Map@@YI_NH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7442)
// source TU  : src/m85/src/mapgen.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool Is_Not_Inland_Or_Mountain_Map(int map_type)
{
	return !Is_Three_Or_Four(map_type);
}
