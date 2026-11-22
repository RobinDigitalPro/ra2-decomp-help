// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00771800 (67 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x327610 (VA 0x00727610, 80 bytes incl. padding)
// RA2 symbol : ?Create_Anim@Voices@WorldDominationTour@@QAEPAVAnim@12@XZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8219)
// source TU  : src/m85/src/wdtvoice.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: a new animation that plays this player's queue.
/// </summary>
Voices::Anim * Voices::Create_Anim(void) // RA2: a new animation that plays this player's queue
{
	return(new Anim(this)); // RA2: as above
}
