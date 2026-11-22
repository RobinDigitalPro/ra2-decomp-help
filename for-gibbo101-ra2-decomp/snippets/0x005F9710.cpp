// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005F9710 (5 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1d02b0 (VA 0x005D02B0, 16 bytes incl. padding)
// RA2 symbol : ?Generic_Theater_Name@@YIXPAD@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.2667)
// source TU  : src/m85/src/objtype.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Puts the generic theater letter into an art name.
/// </summary>
void Generic_Theater_Name(char * name) // RA2: not in TibSun, at 0x005D7C20
{
	name[1] = 'G';
}
