// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00439110 (56 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x36550 (VA 0x00436550, 64 bytes incl. padding)
// RA2 symbol : ?Clear@BombListClass@@QAEXXZ
// similarity : 0.9796 (very-similar, masked instruction tokens; shape 0.7500)
// source TU  : src/m85/src/bomb.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Empties both lists and restarts the visibility timer.
/// </summary>
void BombListClass::Clear(void) // RA2: 0x00436710
{
	// level-2 1.001: Clear does not restart UpdateDelay
	Planted.Delete_All(); // RA2: each list is emptied but keeps its size
	Detectors.Delete_All(); // RA2: as above
}
