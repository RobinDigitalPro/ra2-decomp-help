// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00629710 (9 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1fe280 (VA 0x005FE280, 16 bytes incl. padding)
// RA2 symbol : ?Reset_Grapple_Counters@ParasiteClass@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5333)
// source TU  : src/m85/src/parasite.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Starts the grapple animation (squid) over from its first frame.
/// </summary>
void ParasiteClass::Reset_Grapple_Counters(void) // RA2: 0x006066A0; named for what it does (YR: sub_629710)
{
	GrappleAnimDelay = 0; // RA2: as above
	GrappleAnimFrame = 0; // RA2: as above
}
