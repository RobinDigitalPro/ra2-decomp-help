// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0072DDB0 (316 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2e7fa0 (VA 0x006E7FA0, 320 bytes incl. padding)
// RA2 symbol : ?Load_Interface_Art@@YIXXZ
// similarity : 0.9672 (very-similar, masked instruction tokens; shape 0.9683)
// source TU  : src/m85/src/txtlabel2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: loads the dialog frame's art, the palettes of the shell and lays the frame out for the screen, unless
/// that is done already.
/// </summary>
void __fastcall Load_Interface_Art(void) // RA2: 0x006F2FB0
{
	if (!InterfaceArtLoaded) { // RA2: as above
		Load_Neutral_Mix(); // RA2: as above
		Load_Interface_Shapes(); // RA2: as above
		Load_Art_Palette(ShellPalFile, &ShellPalette, &ShellDrawer); // RA2: as above
		Load_Art_Palette(Shell2PalFile, &Shell2Palette, &Shell2Drawer); // RA2: as above
		Load_Art_Palette(SdbtnanmPalFile, &ButtonAnimPalette, &ButtonAnimDrawer); // RA2: as above
		Layout_Interface_Art(VideoModeWidth, VideoModeHeight); // RA2: as above
		InterfaceArtLoaded = true; // RA2: as above
	}
}
