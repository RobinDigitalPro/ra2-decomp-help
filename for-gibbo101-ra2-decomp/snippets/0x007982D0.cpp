// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007982D0 (111 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x340ff0 (VA 0x00740FF0, 112 bytes incl. padding)
// RA2 symbol : ?Wait_For_Wait_Event@@YIHHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9890)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __fastcall Wait_For_Wait_Event(int seconds, int count) // level-2 1.001: 0x00740FF0 (YR 0x007982D0), waits for one of the first count events, EV_COUNT after the seconds
{
	int remaining = seconds * 1000;
	DWORD index;
	while ((index = WaitForMultipleObjects(count, g_WaitEventHandles, FALSE, 100)) == WAIT_TIMEOUT) {
		remaining -= 100;
		if (remaining <= 0) {
			return(EV_COUNT);
		}
		WOL_Wait_Callback();
	}
	ResetEvent(g_WaitEventHandles[index]);
	return(index);
}
