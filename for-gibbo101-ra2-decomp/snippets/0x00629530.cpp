// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00629530 (119 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1fe0a0 (VA 0x005FE0A0, 128 bytes incl. padding)
// RA2 symbol : ?Clear_Grapple@ParasiteClass@@QAEXXZ
// similarity : 0.9767 (very-similar, masked instruction tokens; shape 0.9053)
// source TU  : src/m85/src/parasite.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Drops the grapple animation (squid) and its tracker entry, and resets the grapple counters.
/// </summary>
void ParasiteClass::Clear_Grapple(void) // RA2: 0x006064C0; named for what it does (YR: sub_629530)
{
	GrappleAnimFrame = 0; // RA2: as above
	GrappleAnimDelay = 0; // RA2: as above
	GrappleState = 0; // RA2: as above
	if (GrappleAnim != NULL) { // RA2: as above
		GrappleAnim->Delete_Me(); // RA2: as above
		GrappleAnim = NULL; // RA2: as above
	}
	if (GrappleAnimGotInvalid) { // RA2: as above
		AnimPtrTracker.Delete(this); // RA2: as above
		GrappleAnimGotInvalid = false; // RA2: as above
	}
}
