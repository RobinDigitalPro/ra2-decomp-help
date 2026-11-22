// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00433060 (274 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x306e0 (VA 0x004306E0, 288 bytes incl. padding)
// RA2 symbol : ?Redraw@BinkHandle@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9381)
// source TU  : src/m85/src/bfiofile2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Draws the current frame again at the movie's own position.
/// </summary>
void BinkHandle::Redraw(void)
{
	if (DrawSurface == VisibleSurface) {
		RECT rc;
		GetClientRect(MainWindow, &rc);
		ClientToScreen(MainWindow, (POINT *)&rc);
		int x = DestRect.X + rc.left;
		int y = DestRect.Y + rc.top;
		Redraw_Frame(DrawSurface, x, y);
	} else {
		Redraw_Frame(DrawSurface, DestRect.X, DestRect.Y);
	}
}
