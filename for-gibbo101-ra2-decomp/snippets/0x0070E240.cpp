// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0070E240 (26 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2cdbb0 (VA 0x006CDBB0, 32 bytes incl. padding)
// RA2 symbol : ?Is_Weapon_Valid@TechnoClass@@QBE_NPBUWeaponDataStruct@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7500)
// source TU  : src/m85/src/techno.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Whether the weapon slot holds a weapon.
/// </summary>
bool TechnoClass::Is_Weapon_Valid(WeaponDataStruct const * wdata) const // RA2: not in TibSun, at 0x6D8640; level-2 1.001: a TechnoClass member (thiscall, called with this in ecx) at 0x6CDBB0
{
	return(wdata != NULL && wdata->Weapon != NULL);
}
