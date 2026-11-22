// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0070DD90 (6 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2cda60 (VA 0x006CDA60, 16 bytes incl. padding)
// RA2 symbol : ?IsNotSprayAttack@TechnoClass@@UBEHXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.2857)
// source TU  : src/m85/src/techno.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// The weapon index used for spray attacks: the secondary one.
/// </summary>
int TechnoClass::IsNotSprayAttack(void) const // RA2: not in TibSun, at 0x6D84F0
{
	return(1);
}
