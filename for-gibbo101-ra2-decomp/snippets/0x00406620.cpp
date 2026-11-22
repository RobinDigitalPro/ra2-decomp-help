// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00406620 (28 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x6630 (VA 0x00406630, 32 bytes incl. padding)
// RA2 symbol : ?AudioEventTypeSetVShift@@YIXPAVAudioEventType@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8571)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Sets the volume shift of an event type, in percent.
/// </summary>
void __fastcall AudioEventTypeSetVShift(AudioEventType * type, int shift) // RA2: 0x00406630
{
	if (shift > 100) { // RA2: as above
		shift = 100; // RA2: as above
	} else if (shift < 0) { // RA2: as above
		shift = 0; // RA2: as above
	}
	type->VShift = shift; // RA2: as above
}
