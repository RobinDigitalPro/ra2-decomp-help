// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00406640 (4 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x6650 (VA 0x00406650, 16 bytes incl. padding)
// RA2 symbol : ?AudioEventTypeSetLoop@@YIXPAVAudioEventType@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.2500)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Sets how often an event type loops; 0 is for ever.
/// </summary>
void __fastcall AudioEventTypeSetLoop(AudioEventType * type, int loop) // RA2: 0x00406650
{
	type->Loop = loop; // RA2: as above
}
