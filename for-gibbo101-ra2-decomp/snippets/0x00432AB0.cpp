// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00432AB0 (279 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x30180 (VA 0x00430180, 288 bytes incl. padding)
// RA2 symbol : ?Set_Position@BinkHandle@@QAEXHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9565)
// source TU  : src/m85/src/bfiofile2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Places the movie with its top left corner at the position specified.
/// </summary>
void BinkHandle::Set_Position(int x, int y)
{
	DestRect = Intersect(DrawSurface->Get_Rect(), Rect(x, y, Bink->Width, Bink->Height));
}
