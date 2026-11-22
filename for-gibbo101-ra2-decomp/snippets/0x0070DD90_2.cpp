// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0070DD90 (6 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2cda70 (VA 0x006CDA70, 16 bytes incl. padding)
// RA2 symbol : ?GetSecondaryWeaponIndex@TechnoClass@@UBEHXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.2857)
// source TU  : src/m85/src/techno.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// The index of the secondary weapon.
/// </summary>
int TechnoClass::GetSecondaryWeaponIndex(void) const // RA2: not in TibSun, at 0x6D8500
{
	return(1);
}
