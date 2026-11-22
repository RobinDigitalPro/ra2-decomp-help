// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00769540 (13 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31f430 (VA 0x0071F430, 16 bytes incl. padding)
// RA2 symbol : ?Territory_Of_Color@@YIII@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7692)
// source TU  : src/m85/src/wdtmap.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: the territory a click map color stands for: colors 0 to 29, and 255 (no territory) for any other.
/// </summary>
unsigned __fastcall Territory_Of_Color(unsigned color) // RA2: 0x0072A870, the executable also has this out of line, though no function calls it; WDT_Write_Map_Ini tests the color with the same two comparisons
{
	return color > 29 ? 255 : color; // RA2: as above
}
