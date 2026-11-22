// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00751010 (45 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x309040 (VA 0x00709040, 48 bytes incl. padding)
// RA2 symbol : ?Resume@VocStaticSound@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9143)
// source TU  : src/m85/src/voc.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Counts one pause less, and resumes the sound's event when it was paused.
/// </summary>
void VocStaticSound::Resume(void) // RA2: as above
{
	if (PauseCount != 0) { // RA2: as above
		if (--PauseCount < 0) { // RA2: as above
			PauseCount = 0; // RA2: as above
		}
		AudioEvent * event = AudioControllerGetEvent(&Controller); // RA2: as above
		if (event != NULL) { // RA2: as above
			AudioEventResume(event); // RA2: as above
		}
	}
}
