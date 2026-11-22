// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004053E0 (71 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x53f0 (VA 0x004053F0, 80 bytes incl. padding)
// RA2 symbol : ?AudioEventPause@@YIXPAVAudioEvent@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8302)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Pauses one event; a waiting event keeps the time it has left.
/// </summary>
void __fastcall AudioEventPause(AudioEvent * event) // RA2: 0x004053F0
{
	if (!AudioEventIsPaused(event)) { // RA2: as above
		if (event->state == AUDIO_EVENT_WAITING) { // RA2: as above
			event->timeOut -= AudioGetTime(); // RA2: as above
		}
	}
	LockAcquire(&event->paused); // RA2: as above
}
