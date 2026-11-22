// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006ABC40 (20 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x276fe0 (VA 0x00676FE0, 32 bytes incl. padding)
// RA2 symbol : ?Zoom_Mode_Control@SidebarClass@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.4545)
// source TU  : src/m85/src/sidebar.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/***********************************************************************************************
 * SidebarClass::Zoom_Mode_Control -- Handles the zoom mode toggle operation.                  *
 *                                                                                             *
 *    This is the function that is called when the map button is pressed. It will toggle       *
 *    between the different modes that the radar map can assume.                               *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/31/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
void SidebarClass::Zoom_Mode_Control(void)
{
	/*
	**	If radar is active, cycle as follows:
	**	Zoomed => not zoomed
	**	not zoomed => player status (multiplayer only)
	**	player status => radar spying readout
	**	radar spying readout => zoomed
	*/
	if (Session.Type!=GAME_NORMAL) {
		SpecialDialog = SDLG_SPECIAL; // level-2 1.001: the map button only raises the special dialog (1.006 cycles the radar modes)
	}
}
