// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007342C0 (13 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2ed710 (VA 0x006ED710, 16 bytes incl. padding)
// RA2 symbol : ?Is_Techno@AbstractClass@@QBE_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8235)
// source TU  : src/m85/src/uicmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Whether this is a TechnoClass object, by its abstract flags.
/// </summary>
bool AbstractClass::Is_Techno(void) const // RA2: 0x006F8A70
{
	if (this == NULL) { // RA2: as above
		return false; // RA2: bit 0 of the abstract flags marks a techno; a null object is none
	}
	bool flag = AbstractFlags & 1; // RA2: as above
	return flag; // RA2: as above
}
