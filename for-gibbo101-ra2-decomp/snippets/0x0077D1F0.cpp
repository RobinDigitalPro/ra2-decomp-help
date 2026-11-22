// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0077D1F0 (11 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x3276a0 (VA 0x007276A0, 16 bytes incl. padding)
// RA2 symbol : ??1Anim@Voices@WorldDominationTour@@UAE@XZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.4444)
// source TU  : src/m85/src/wdtvoice.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

Voices::Anim::~Anim(void) // RA2: a new animation that plays this player's queue
{
}
