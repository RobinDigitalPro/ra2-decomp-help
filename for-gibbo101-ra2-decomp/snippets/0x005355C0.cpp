// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005355C0 (16 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x119de0 (VA 0x00519DE0, 16 bytes incl. padding)
// RA2 symbol : ?Fetch_Main_Menu_Theme@@YI?AW4ThemeType@@XZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/init.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

ThemeType Fetch_Main_Menu_Theme(void)
{
	return(Theme.From_Name("INTRO"));
}
