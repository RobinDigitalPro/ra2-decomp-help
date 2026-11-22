// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0070DC60 (15 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2cd950 (VA 0x006CD950, 16 bytes incl. padding)
// RA2 symbol : ?Has_Turret_Weapons@TechnoClass@@QAE_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8889)
// source TU  : src/m85/src/techno.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Whether the type has turret weapons to choose from.
/// </summary>
bool TechnoClass::Has_Turret_Weapons(void) // RA2: not in TibSun, at 0x6D83E0
{
	return(Techno_Type_Class()->Has_Turret_Weapons());
}
