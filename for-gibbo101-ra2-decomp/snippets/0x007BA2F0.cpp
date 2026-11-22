// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007BA2F0 (13 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x35efa0 (VA 0x0075EFA0, 16 bytes incl. padding)
// RA2 symbol : ?Unblock_Mouse@WWMouseClass@@AAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7273)
// source TU  : src/m85/src/wwmouse.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Releases the mouse lock taken by Block_Mouse.
/// This routine hands the mouse back to the background timer callback so that cursor
/// updates may resume.
/// </summary>
void WWMouseClass::Unblock_Mouse(void)
{
	ReleaseMutex(MouseMutex);
}
