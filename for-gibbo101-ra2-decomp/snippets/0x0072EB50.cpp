// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0072EB50 (211 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2e8d40 (VA 0x006E8D40, 224 bytes incl. padding)
// RA2 symbol : ?Load_Interface_Shapes@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8632)
// source TU  : src/m85/src/txtlabel2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: loads the shapes of the dialog frame.
/// </summary>
void __fastcall Load_Interface_Shapes(void) // RA2: 0x006F3D50
{
	Slide_Button_Shape = (ShapeSet *)Load_Alloc_Data(SdbtnanmShpFile, SlideButtonAllocated); // RA2: as above
	ArtSlideMPButton = (ShapeSet *)Load_Alloc_Data(SdmpbtnShpFile, ArtSlideMPButtonAllocated); // RA2: as above
	ArtSlideWarning = (ShapeSet *)Load_Alloc_Data(SdwrntmpShpFile, ArtSlideWarningAllocated); // RA2: as above
	Art_Dialog_Back640 = (ShapeSet *)Load_Alloc_Data(MnscrnsShpFile, ArtDialogBack640Allocated); // RA2: as above
	Art_Dialog_Back = (ShapeSet *)Load_Alloc_Data(MnscrnlShpFile, ArtDialogBackAllocated); // RA2: as above
	ArtSlideTop = (ShapeSet *)Load_Alloc_Data(SdtpShpFile, ArtSlideTopAllocated); // RA2: as above
	ArtSlideButtonBack = (ShapeSet *)Load_Alloc_Data(SdbtnbkgdShpFile, ArtSlideButtonBackAllocated); // RA2: as above
	ArtSlideBottom = (ShapeSet *)Load_Alloc_Data(SdbtmShpFile, ArtSlideBottomAllocated); // RA2: as above
	ArtLowerScreen640 = (ShapeSet *)Load_Alloc_Data(LwscrnsShpFile, ArtLowerScreen640Allocated); // RA2: as above
	ArtLowerScreen = (ShapeSet *)Load_Alloc_Data(LwscrnlShpFile, ArtLowerScreenAllocated); // RA2: as above
}
