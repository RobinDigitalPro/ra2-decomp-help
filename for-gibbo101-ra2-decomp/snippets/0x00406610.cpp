// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00406610 (13 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x6620 (VA 0x00406620, 16 bytes incl. padding)
// RA2 symbol : ?AudioEventTypeSetFShift@@YIXPAVAudioEventType@@HH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7273)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Sets the lowest and highest pitch shift of an event type.
/// </summary>
void __fastcall AudioEventTypeSetFShift(AudioEventType * type, int minShift, int maxShift) // RA2: 0x00406620
{
	type->MinFDelta = minShift; // RA2: as above
	type->MaxFDelta = maxShift; // RA2: as above
}
