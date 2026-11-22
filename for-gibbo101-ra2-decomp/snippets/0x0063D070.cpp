// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063D070 (120 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2119e0 (VA 0x006119E0, 128 bytes incl. padding)
// RA2 symbol : ?Planning_Adjusted_Pixel@@YIHABVRGBClass@@0H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8889)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __fastcall Planning_Adjusted_Pixel(RGBClass const & rgb, RGBClass const & target, int ratio) // RA2: 0x00619E00; the pixel of a color brought ratio/256 toward target
{
	RGBClass color = rgb;
	color.Adjust(ratio, target);
	return ((color.Get_Red() >> DSurface::RedLeft) << DSurface::RedRight) | ((color.Get_Green() >> DSurface::GreenLeft) << DSurface::GreenRight) | ((color.Get_Blue() >> DSurface::BlueLeft) << DSurface::BlueRight);
}
