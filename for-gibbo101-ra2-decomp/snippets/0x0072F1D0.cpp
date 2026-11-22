// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0072F1D0 (149 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2e9350 (VA 0x006E9350, 160 bytes incl. padding)
// RA2 symbol : ?Free_Interface_Rects@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8706)
// source TU  : src/m85/src/txtlabel2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: frees the areas the dialog frame was laid out in.
/// </summary>
void __fastcall Free_Interface_Rects(void) // RA2: 0x006F4360
{
	operator delete(SlideButtonRect); // RA2: as above
	SlideButtonRect = NULL; // RA2: as above
	operator delete(SlideMPButtonRect); // RA2: as above
	SlideMPButtonRect = NULL; // RA2: as above
	operator delete(SlideWarningRect); // RA2: as above
	SlideWarningRect = NULL; // RA2: as above
	operator delete(DialogBackRect); // RA2: as above
	DialogBackRect = NULL; // RA2: as above
	operator delete(SlideTopRect); // RA2: as above
	SlideTopRect = NULL; // RA2: as above
	operator delete(Button_Strip_Top); // RA2: as above
	Button_Strip_Top = NULL; // RA2: as above
	operator delete(Button_Strip_Bottom); // RA2: as above
	Button_Strip_Bottom = NULL; // RA2: as above
	operator delete(LowerScreenRect); // RA2: as above
	LowerScreenRect = NULL; // RA2: as above
}
