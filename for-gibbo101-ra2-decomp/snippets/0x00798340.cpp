// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00798340 (32 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x341060 (VA 0x00741060, 32 bytes incl. padding)
// RA2 symbol : ?Reset_Wait_Events@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Reset_Wait_Events(void) // RA2: 0x00752930, not in TibSun: resets every wait event
{
	for (int i = 0; i < EV_COUNT; i++) { // RA2: as above
		ResetEvent(g_WaitEventHandles[i]); // RA2: as above
	}
}
