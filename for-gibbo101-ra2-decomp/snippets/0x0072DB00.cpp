// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0072DB00 (177 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2e7de0 (VA 0x006E7DE0, 192 bytes incl. padding)
// RA2 symbol : ?Load_Side_Animation_Shapes@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8276)
// source TU  : src/m85/src/txtlabel2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: loads the shapes of the side animation, in the size that fits the screen.
/// </summary>
void __fastcall Load_Side_Animation_Shapes(void) // RA2: 0x006F2DF0
{
	if (VideoModeWidth == 640) { // RA2: as above
		Art_Side_Animation = Load_Alloc_Data(FsasmShpFile, ArtSideAnimationAllocated); // RA2: as above
		Art_Button_Corner = Load_Alloc_Data(FsbcsmShpFile, ArtButtonCornerAllocated); // RA2: as above
		Art_Side_Strip = Load_Alloc_Data(FsssmShpFile, ArtSideStripAllocated); // RA2: as above
		Art_Button_Back = Load_Alloc_Data(FsbkgdsmShpFile, ArtButtonBackAllocated); // RA2: as above
	} else {
		Art_Side_Animation = Load_Alloc_Data(FsalgShpFile, ArtSideAnimationAllocated); // RA2: as above
		Art_Button_Corner = Load_Alloc_Data(FsbclgShpFile, ArtButtonCornerAllocated); // RA2: as above
		Art_Side_Strip = Load_Alloc_Data(FsslgShpFile, ArtSideStripAllocated); // RA2: as above
		Art_Button_Back = Load_Alloc_Data(FsbkgdlgShpFile, ArtButtonBackAllocated); // RA2: as above
	}
}
