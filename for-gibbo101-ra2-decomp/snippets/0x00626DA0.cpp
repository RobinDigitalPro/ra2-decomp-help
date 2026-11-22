// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00626DA0 (592 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1fb930 (VA 0x005FB930, 592 bytes incl. padding)
// RA2 symbol : ?Palette_Scheme_Count@@YIHXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/palette.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int Palette_Scheme_Count(void) // RA2: 0x00603D50, how many palettes have a scheme list
{
	SchemeLibrary * library = Scheme_Library(); // RA2: the executable keeps the library in a local here (the loop's register use depends on it)
	SchemeListIterator it; // RA2: as above
	int count = 0; // RA2: as above
	DynamicVectorClass<ColorScheme *> * schemes = it.Next(); // RA2: as above
	while (schemes != NULL) { // RA2: as above
		count++; // RA2: as above
		schemes = it.Next(); // RA2: as above
	}
	return(count); // RA2: as above
}
