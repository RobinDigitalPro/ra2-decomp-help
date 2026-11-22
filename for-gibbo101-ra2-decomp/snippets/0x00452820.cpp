// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00452820 (128 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x4d710 (VA 0x0044D710, 128 bytes incl. padding)
// RA2 symbol : ?Rotate_Overpowerer@BuildingClass@@QAEXPAVInfantryClass@@@Z
// similarity : 0.9608 (very-similar, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/building.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Moves the infantry to the end of the list of those overpowering this building.
/// </summary>
void BuildingClass::Rotate_Overpowerer(InfantryClass * infantry) // RA2: not in TibSun, at 0x44DA20
{
	Overpowerers.Delete(infantry);
	Overpowerers.Add(infantry);
}
