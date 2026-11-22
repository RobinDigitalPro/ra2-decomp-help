// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0050BA00 (656 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xf4a70 (VA 0x004F4A70, 656 bytes incl. padding)
// RA2 symbol : ?Update_Laser_Color@HouseClass@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/house.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void HouseClass::Update_Laser_Color(void) // RA2: RA2's form
{
	double red = RemapColorRGB.Get_Red(); // RA2: as above
	double green = RemapColorRGB.Get_Green(); // RA2: as above
	double blue = RemapColorRGB.Get_Blue(); // RA2: as above
	Normalize_Color(red, green, blue); // RA2: as above
	if (red < 96.0) { // RA2: as above
		red = 0; // RA2: as above
	}
	if (green < 96.0) { // RA2: as above
		green = 0; // RA2: as above
	}
	if (blue < 96.0) { // RA2: as above
		blue = 0; // RA2: as above
	}
	Normalize_Color(red, green, blue); // RA2: as above
	LaserColor.Set(red, green, blue); // RA2: as above
}
