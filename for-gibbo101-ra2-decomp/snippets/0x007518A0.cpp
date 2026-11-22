// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007518A0 (31 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x3098d0 (VA 0x007098D0, 32 bytes incl. padding)
// RA2 symbol : ?Controller_Set_Voc@@YIXPAUAudioController@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9565)
// source TU  : src/m85/src/voc.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Points a controller at the event type of a sound effect, without an event.
/// </summary>
/// <param name="controller">The controller to point.</param>
/// <param name="voc">The sound effect number.</param>
void __fastcall Controller_Set_Voc(AudioController * controller, int voc) // RA2: sets only the type of the controller
{
	if (voc >= 0 && voc < Vocs.Count()) { // RA2: as above
		controller->SetEvent(NULL, (VocClass *)Vocs[voc]->Event); // RA2: as above
	}
}
