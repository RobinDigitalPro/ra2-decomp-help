// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007B84F0 (278 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x35d120 (VA 0x0075D120, 288 bytes incl. padding)
// RA2 symbol : ?Start_Mouse_Thread@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9367)
// source TU  : src/m85/src/wwmouse.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Start_Mouse_Thread(void) // RA2: not in TibSun
{
	char buffer[1024]; // RA2: as above

	if (MouseMutex == NULL) { // RA2: as above
		MouseMutex = CreateMutex(NULL, FALSE, NULL); // RA2: as above
	}
	if (!MouseThreadActive && MouseMutex != NULL) { // RA2: as above
		MouseThreadInfo.Reset(); // RA2: as above
		MouseThread = CreateThread(NULL, 0x1000, Mouse_Thread, &MouseThreadInfo, 0, &MouseThreadID); // RA2: as above
		if (MouseThread != NULL) { // RA2: as above
			MouseThreadActive = 1; // RA2: as above
			if (!SetThreadPriority(MouseThread, THREAD_PRIORITY_TIME_CRITICAL)) { // RA2: as above
				FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 0, buffer, sizeof(buffer), NULL); // RA2: as above
				DebugString("Unable to change the priority of the mouse thread - %s\n", buffer); // RA2: as above
				while (!MouseThreadInfo.Done) { // RA2: as above
					Sleep(0); // RA2: as above
				}
				WaitForSingleObject(MouseThread, 5000); // RA2: as above
				CloseHandle(MouseThread); // RA2: as above
				MouseThreadActive = 0; // RA2: as above
			}
		}
	}
}
