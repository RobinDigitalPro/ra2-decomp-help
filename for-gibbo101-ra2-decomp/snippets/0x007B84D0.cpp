// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007B84D0 (25 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x35d100 (VA 0x0075D100, 32 bytes incl. padding)
// RA2 symbol : ?Process_Mouse_Unthreaded@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6957)
// source TU  : src/m85/src/wwmouse.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/***********************************************************************************************
 * Process_Mouse_Unthreaded -- Process the mouse from the caller's thread.                     *
 *                                                                                             *
 *    This is called by the audio service loop. It processes the mouse only when there is no   *
 *    mouse thread doing so.                                                                   *
 *=============================================================================================*/
void Process_Mouse_Unthreaded(void) // RA2: the executable's function that audio.cpp calls
{
	if (!MouseThreadActive && _MousePtr != NULL) { // RA2: as above
		_MousePtr->Process_Mouse(); // RA2: as above
	}
}
