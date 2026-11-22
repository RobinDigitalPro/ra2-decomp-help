// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004065D0 (4 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x65e0 (VA 0x004065E0, 16 bytes incl. padding)
// RA2 symbol : ?AudioEventTypeSetLimit@@YIXPAVAudioEventType@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.2500)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Sets how many events of an event type may play at once.
/// </summary>
void __fastcall AudioEventTypeSetLimit(AudioEventType * type, int limit) // RA2: 0x004065E0
{
	type->Limit = limit; // RA2: as above
}
