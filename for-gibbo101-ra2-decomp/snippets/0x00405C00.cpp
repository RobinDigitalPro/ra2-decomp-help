// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00405C00 (315 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x5c10 (VA 0x00405C10, 320 bytes incl. padding)
// RA2 symbol : ?Release@AudioController@@QAEXXZ
// similarity : 0.9756 (very-similar, masked instruction tokens; shape 0.9704)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Stops the sound of a handle and detaches it from the audio library.
/// </summary>
void AudioController::Release(void) // RA2: 0x00405C10
{
	Stop(); // RA2: as above
	AudioIndex = NULL; // RA2: as above
}
