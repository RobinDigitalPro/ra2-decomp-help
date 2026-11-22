// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00406600 (13 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x6610 (VA 0x00406610, 16 bytes incl. padding)
// RA2 symbol : ?AudioEventTypeSetDelay@@YIXPAVAudioEventType@@HH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7273)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Sets the shortest and longest delay between the samples of an event type.
/// </summary>
void __fastcall AudioEventTypeSetDelay(AudioEventType * type, int minDelay, int maxDelay) // RA2: 0x00406610
{
	type->MinDelay = minDelay; // RA2: as above
	type->MaxDelay = maxDelay; // RA2: as above
}
