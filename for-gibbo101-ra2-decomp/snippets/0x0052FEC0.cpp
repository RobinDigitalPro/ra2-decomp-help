// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0052FEC0 (202 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x114f50 (VA 0x00514F50, 208 bytes incl. padding)
// RA2 symbol : ?Darken_Surface@@YIXPAVSurface@@_N@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9620)
// source TU  : src/m85/src/init.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Dims a surface and shows it.
/// This routine is used to darken the screen behind a dialog box. A null surface means the
/// hidden surface.
/// </summary>
/// <param name="surface">The surface to darken, or NULL for the hidden surface.</param>
/// <param name="update">Should the result be copied to the visible surface?</param>
void Darken_Surface(Surface * surface, bool update) // RA2: 0x005159B0, not in TibSun: dims the screen behind a dialog; update copies the result to the visible surface
{
	if (surface == NULL) { // RA2: as above
		surface = HiddenSurface; // RA2: as above
	}
	surface->Fill(0); // RA2: as above
	int width = surface->Get_Width(); // RA2: as above
	int height = surface->Get_Height(); // RA2: as above
	Rect rect(0, 0, width, height); // RA2: as above
	BSurface * work = new BSurface(width, height, 2); // RA2: as above
	Draw_Interface_Screen(work, rect, false); // RA2: as above
	surface->Blit_From(*work, false, true); // RA2: as above
	delete work; // RA2: as above
	if (update) { // RA2: as above
		Update_Visible_Surface(false, surface, NULL); // RA2: as above
	}
}
