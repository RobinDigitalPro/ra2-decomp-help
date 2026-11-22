// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00406530 (7 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x6540 (VA 0x00406540, 16 bytes incl. padding)
// RA2 symbol : ?AudioEventTypeSetDecay@@YIXPAVAudioEventType@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.3077)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Sets how many samples of an event type are decay samples.
/// </summary>
void __fastcall AudioEventTypeSetDecay(AudioEventType * type, int decay) // RA2: 0x00406540
{
	type->Decay = decay; // RA2: as above
}
