// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0072DEF0 (183 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2e80e0 (VA 0x006E80E0, 192 bytes incl. padding)
// RA2 symbol : ?Free_Interface_Art@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9072)
// source TU  : src/m85/src/txtlabel2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: frees the dialog frame's art and the palettes of the shell, when they are loaded.
/// </summary>
void __fastcall Free_Interface_Art(void) // RA2: 0x006F30F0
{
	if (InterfaceArtLoaded) { // RA2: as above
		InterfaceArtLoaded = false; // RA2: as above
		Free_Interface_Shapes(); // RA2: as above
		Free_Interface_Palettes(); // RA2: as above
		Free_Interface_Rects(); // RA2: as above
		Release_Neutral_Mix(); // RA2: as above
	}
}
