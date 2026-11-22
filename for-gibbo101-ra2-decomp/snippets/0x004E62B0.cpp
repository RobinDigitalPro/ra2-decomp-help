// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004E62B0 (29 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xd2250 (VA 0x004D2250, 32 bytes incl. padding)
// RA2 symbol : ?Get_CPU_Type_Name@@YIPBDXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8571)
// source TU  : src/m85/src/getcpu.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

char const * Get_CPU_Type_Name(void) // RA2: not in TibSun (0x004D2B80)
{
	static char const * const names[CPU_COUNT] = { // RA2: the table at 0x007D8838
		"486", // RA2: as above
		"Pentium", // RA2: as above
		"Pentium Pro", // RA2: as above
		"Pentium II", // RA2: as above
		"Pentium III", // RA2: as above
		"Celeron", // RA2: as above
		"Pentium 4", // RA2: as above
		"AMD", // RA2: as above
		"Cyrix" // RA2: as above
	};

	int type = Get_CPU_Type(); // RA2: as above
	if (type > CPU_UNKNOWN && type < CPU_COUNT) { // RA2: as above
		return names[type]; // RA2: as above
	}
	return "Unknown"; // RA2: as above
}
