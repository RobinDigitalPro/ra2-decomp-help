// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00405160 (16 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x5140 (VA 0x00405140, 16 bytes incl. padding)
// RA2 symbol : ?AudioEventTypeGetType@@YIIPAVAudioEventType@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// The "Type" flags of an event type.
/// </summary>
unsigned int __fastcall AudioEventTypeGetType(AudioEventType * type) // RA2: 0x00405140
{
	if (!audioEventsReady) { // RA2: as above
		return 0; // RA2: as above
	}
	return type->Type; // RA2: as above
}
