// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004052E0 (9 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x52f0 (VA 0x004052F0, 16 bytes incl. padding)
// RA2 symbol : ?AudioEventSetFlag8@@YIXPAVAudioEvent@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5333)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Marks an event as past its attack.
/// </summary>
void __fastcall AudioEventSetFlag8(AudioEvent * event) // RA2: 0x004052F0
{
	event->flags |= mAUDIO_EVENT_NO_ATTACK; // RA2: as above
}
