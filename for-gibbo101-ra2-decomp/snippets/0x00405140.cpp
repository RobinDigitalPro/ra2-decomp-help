// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00405140 (20 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x5120 (VA 0x00405120, 32 bytes incl. padding)
// RA2 symbol : ?AudioEventTypeMinVolume@@YIMPAVAudioEventType@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5385)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// The lowest volume an event type is played at.
/// </summary>
float __fastcall AudioEventTypeMinVolume(AudioEventType * type) // RA2: 0x00405120
{
	if (!audioEventsReady) { // RA2: as above
		return 0.0f; // RA2: as above
	}
	return type->MinVolume; // RA2: as above
}
