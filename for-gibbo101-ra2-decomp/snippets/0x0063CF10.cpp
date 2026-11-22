// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063CF10 (165 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x211880 (VA 0x00611880, 176 bytes incl. padding)
// RA2 symbol : ?Planning_Dim_Color@@YIHPAVTechnoClass@@@Z
// similarity : 0.9778 (very-similar, masked instruction tokens; shape 0.8911)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __fastcall Planning_Dim_Color(TechnoClass * techno) // RA2: 0x00619CA0; the pixel of the house color of a techno brought 80/256 toward black
{
	RGBClass color = Planning_House_Color(techno); // RA2: as above
	color.Adjust(0x50, BlackColor); // RA2: as above
	return ((color.Get_Green() >> DSurface::GreenLeft) << DSurface::GreenRight) | ((color.Get_Red() >> DSurface::RedLeft) << DSurface::RedRight) | ((color.Get_Blue() >> DSurface::BlueLeft) << DSurface::BlueRight); // RA2: as above
}
