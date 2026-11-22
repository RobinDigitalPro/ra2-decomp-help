// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007B86B0 (116 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x35d2e0 (VA 0x0075D2E0, 128 bytes incl. padding)
// RA2 symbol : ?Kill_Mouse_Thread@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8462)
// source TU  : src/m85/src/wwmouse.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/***********************************************************************************************
 * Kill_Mouse_Thread -- Stop the mouse thread and release the mouse mutex.                     *
 *=============================================================================================*/
void Kill_Mouse_Thread(void) // RA2: not in TibSun
{
	if (MouseThreadActive) { // RA2: as above
		MouseThreadInfo.Quit = 1; // RA2: as above
		while (!MouseThreadInfo.Done) { // RA2: as above
			Sleep(0); // RA2: as above
		}
		WaitForSingleObject(MouseThread, 5000); // RA2: as above
		CloseHandle(MouseThread); // RA2: as above
		MouseThreadActive = 0; // RA2: as above
	}
	if (MouseMutex != NULL) { // RA2: as above
		CloseHandle(MouseMutex); // RA2: as above
		MouseMutex = NULL; // RA2: as above
	}
}
