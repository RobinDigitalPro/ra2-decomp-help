// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0070E1E0 (90 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2cdb50 (VA 0x006CDB50, 96 bytes incl. padding)
// RA2 symbol : ?Is_Valid_Weapon_Index@TechnoClass@@QAEHH@Z
// similarity : 0.9730 (very-similar, masked instruction tokens; shape 0.9250)
// source TU  : src/m85/src/techno.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Whether the index names a weapon: -1, the primary or secondary one, or a turret weapon of the type.
/// </summary>
int TechnoClass::Is_Valid_Weapon_Index(int which) // RA2: not in TibSun, at 0x6D85E0
{
	bool basic = which < 2;
	bool turret = Techno_Type_Class()->Has_Turret_Weapons() && which < Techno_Type_Class()->WeaponCount;
	if (which >= -1 && (basic || turret)) {
		return(1);
	}
	return(0);
}
