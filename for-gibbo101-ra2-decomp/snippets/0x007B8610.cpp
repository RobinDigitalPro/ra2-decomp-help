// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007B8610 (160 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x35d240 (VA 0x0075D240, 160 bytes incl. padding)
// RA2 symbol : ?Mouse_Thread@@YGKPAX@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/wwmouse.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/***********************************************************************************************
 * Mouse_Thread -- The thread procedure that processes the mouse.                              *
 *=============================================================================================*/
DWORD WINAPI Mouse_Thread(LPVOID parameter) // RA2: not in TibSun
{
	MouseThreadInfoStruct * info = (MouseThreadInfoStruct *)parameter; // RA2: as above

	info->Started = 1; // RA2: as above
	info->Done = 0; // RA2: as above
	while (!info->Quit) { // RA2: as above
		_MousePtr->Block_Mouse(); // RA2: as above
		if (_MousePtr != NULL) { // RA2: as above
			_MousePtr->Process_Mouse(); // RA2: as above
		}
		_MousePtr->Unblock_Mouse(); // RA2: as above
		Sleep((DWORD)info->Delay); // RA2: as above
		info->Count++; // RA2: as above
	}
	info->Done = 1; // RA2: as above
	return(0); // RA2: as above
}
