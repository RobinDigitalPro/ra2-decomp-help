// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0072DFB0 (497 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2e81a0 (VA 0x006E81A0, 512 bytes incl. padding)
// RA2 symbol : ?Reload_Art_Set@@YIXXZ
// similarity : 0.9806 (very-similar, masked instruction tokens; shape 0.9321)
// source TU  : src/m85/src/txtlabel2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: frees the dialog frame's art and loads it again, as at the end of a game.
/// </summary>
void __fastcall Reload_Art_Set(void) // RA2: 0x006F31B0
{
	Free_Interface_Art(); // RA2: as above
	Load_Interface_Art(); // RA2: as above
}
