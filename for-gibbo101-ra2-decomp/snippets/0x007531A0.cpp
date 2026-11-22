// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007531A0 (162 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x30b150 (VA 0x0070B150, 176 bytes incl. padding)
// RA2 symbol : ?Speech_Free_All@@YIXXZ
// similarity : 0.9800 (very-similar, masked instruction tokens; shape 0.8772)
// source TU  : src/m85/src/vox.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Speech_Free_All(void) // RA2: 0x00716590; stops the speech, drops the waiting ones and deletes every VoxClass
{
	Speech_Stop(true); // RA2: as above
	while (Voxs.Count() > 0) { // RA2: as above
		delete Voxs[0]; // RA2: as above
	}
}
