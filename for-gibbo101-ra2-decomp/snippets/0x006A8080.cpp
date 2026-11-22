// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006A8080 (9 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x273de0 (VA 0x00673DE0, 16 bytes incl. padding)
// RA2 symbol : ?Cameos_Width@SidebarClass@@SIHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.4615)
// source TU  : src/m85/src/sidebar.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/***********************************************************************************************
 * SidebarClass::StripClass::StripClass -- Default constructor for the side strip class.       *
 *                                                                                             *
 *    This constructor is used to reset the side strip to default empty state.                 *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/31/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
int __fastcall SidebarClass::Cameos_Width(int value) // RA2: as above
{
	return CameoWidth * value; // RA2: as above
}
