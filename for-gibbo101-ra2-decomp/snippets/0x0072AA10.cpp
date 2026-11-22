// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0072AA10 (47 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2e6c10 (VA 0x006E6C10, 48 bytes incl. padding)
// RA2 symbol : ?Inflate_Rect@@YIXAAV?$TRect@H@@HH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9756)
// source TU  : src/m85/src/txtlabel2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: moves the left and right edges of a rectangle in by one amount and the top and bottom edges by another.
/// </summary>
void __fastcall Inflate_Rect(Rect & rect, int dx, int dy) // RA2: 0x006F1B30
{
	rect.X += dx; // RA2: as above
	rect.Y += dy; // RA2: as above
	rect.Width -= dx * 2; // RA2: as above
	rect.Height -= dy * 2; // RA2: as above
}
