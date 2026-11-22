// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00405170 (18 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x5150 (VA 0x00405150, 32 bytes incl. padding)
// RA2 symbol : ?AudioEventTypeName@@YIPBDPAVAudioEventType@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.4615)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// The name of an event type.
/// </summary>
char const * __fastcall AudioEventTypeName(AudioEventType * type) // RA2: 0x00405150
{
	if (!audioEventsReady) { // RA2: as above
		return "no events"; // RA2: as above
	}
	return type->Name; // RA2: as above
}
