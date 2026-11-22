// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00405BE0 (18 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x5bf0 (VA 0x00405BF0, 32 bytes incl. padding)
// RA2 symbol : ?Init@AudioController@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.4615)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Forgets the event of a handle and its type; the sound it started keeps playing.
/// </summary>
void AudioController::Init(void) // RA2: 0x00405BF0
{
	AudioIndex = (void **)&AudioIDXData::Instance; // RA2: as above
	Event = NULL; // RA2: as above
	Stamp = 0; // RA2: as above
	EventType = NULL; // RA2: as above
}
