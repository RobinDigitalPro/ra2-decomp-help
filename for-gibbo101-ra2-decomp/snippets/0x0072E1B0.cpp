// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0072E1B0 (165 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2e83a0 (VA 0x006E83A0, 176 bytes incl. padding)
// RA2 symbol : ?Relayout_Interface_Art@@YIXHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8911)
// source TU  : src/m85/src/txtlabel2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: lays the dialog frame out again for a screen size.
/// </summary>
void __fastcall Relayout_Interface_Art(int width, int height) // RA2: 0x006F33B0
{
	Free_Interface_Rects(); // RA2: as above
	Layout_Interface_Art(width, height); // RA2: as above
}
