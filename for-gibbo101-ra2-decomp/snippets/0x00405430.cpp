// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00405430 (95 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x5440 (VA 0x00405440, 96 bytes incl. padding)
// RA2 symbol : ?AudioEventResume@@YIXPAVAudioEvent@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9825)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Resumes one paused event; a waiting event gets its time back.
/// </summary>
void __fastcall AudioEventResume(AudioEvent * event) // RA2: 0x00405440
{
	if (AudioEventIsPaused(event)) { // RA2: as above
		LockRelease(&event->paused); // RA2: as above
		if (!AudioEventIsPaused(event)) { // RA2: as above
			if (event->state == AUDIO_EVENT_WAITING) { // RA2: as above
				event->timeOut += AudioGetTime(); // RA2: as above
			}
		}
	}
}
