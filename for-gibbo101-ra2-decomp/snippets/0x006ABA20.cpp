// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006ABA20 (25 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x276df0 (VA 0x00676DF0, 32 bytes incl. padding)
// RA2 symbol : ?Is_Hover_Live@SelectClass@StripClass@SidebarClass@@QAE_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7407)
// source TU  : src/m85/src/sidebar.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Is the mouse over this cameo while input is accepted?
/// </summary>
bool SidebarClass::StripClass::SelectClass::Is_Hover_Live(void) // level-2 1.001: 0x676DF0, no references
{
	return(IsHovered && !IgnoreInput);
}
