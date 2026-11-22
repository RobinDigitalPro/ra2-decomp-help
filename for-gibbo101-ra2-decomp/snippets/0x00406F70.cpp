// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00406F70 (129 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x6ea0 (VA 0x00406EA0, 144 bytes incl. padding)
// RA2 symbol : ?Audio_Service@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8235)
// source TU  : src/m85/src/audio.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Audio_Service(void)
{
	if (!AudioServiceBusy && AudioMainDevice) {
		AudioServiceBusy = 1;
		TimeStamp now = AudioGetTime();
		if (now - AudioServiceLast > 33) {
			AudioServiceAllEvents();
			Sound_Service();
			Speech_Service();
			Theme.AI();
			Process_Mouse_Unthreaded(); // RA2: as above
			AudioServiceLast = now;
		}
		AudioServiceBusy = 0;
	}
}
