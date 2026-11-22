// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0072EC30 (64 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2e8e20 (VA 0x006E8E20, 64 bytes incl. padding)
// RA2 symbol : ?Load_Interface_Palettes@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/txtlabel2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: loads the palettes of the shell.
/// </summary>
void __fastcall Load_Interface_Palettes(void) // RA2: 0x006F3E30
{
	Load_Art_Palette(ShellPalFile, &ShellPalette, &ShellDrawer); // RA2: as above
	Load_Art_Palette(Shell2PalFile, &Shell2Palette, &Shell2Drawer); // RA2: as above
	Load_Art_Palette(SdbtnanmPalFile, &ButtonAnimPalette, &ButtonAnimDrawer); // RA2: as above
}
