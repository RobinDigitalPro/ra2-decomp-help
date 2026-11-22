// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0077D210 (34 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x330bc0 (VA 0x00730BC0, 48 bytes incl. padding)
// RA2 symbol : ?Spaces_To_Underscores@@YIXPAD@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6667)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Spaces_To_Underscores(char * text) // RA2: 0x0073C040, turns every space of the text into an underscore, nothing calls it
{
	for (char * space = strchr(text, ' '); space != NULL; space = strchr(space, ' ')) { // RA2: as above
		*space = '_';
	}
}
