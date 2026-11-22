// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0072A9E0 (34 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2e6be0 (VA 0x006E6BE0, 48 bytes incl. padding)
// RA2 symbol : ?Inflate_Rect@@YIXAAV?$TRect@H@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6667)
// source TU  : src/m85/src/txtlabel2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: moves each edge of a rectangle in by an amount.
/// </summary>
void __fastcall Inflate_Rect(Rect & rect, int amount) // RA2: 0x006F1B00
{
	rect.X += amount; // RA2: as above
	rect.Y += amount; // RA2: as above
	rect.Width -= amount * 2; // RA2: as above
	rect.Height -= amount * 2; // RA2: as above
}
