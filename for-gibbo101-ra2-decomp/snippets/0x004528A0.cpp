// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004528A0 (158 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x4d790 (VA 0x0044D790, 160 bytes incl. padding)
// RA2 symbol : ?Is_In_Psychic_Range@BuildingClass@@QAE_NPBVAbstractClass@@@Z
// similarity : 0.9672 (very-similar, masked instruction tokens; shape 0.9839)
// source TU  : src/m85/src/building.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Is the target within this building's psychic detection radius?
/// </summary>
bool BuildingClass::Is_In_Psychic_Range(AbstractClass const * target) // RA2: not in TibSun, at 0x44DAA0
{
	Coord a = Center_Coord();
	Coord b = target->Center_Coord();
	return(a.Distance_To(b) <= Class->PsychicDetectionRadius << 8);
}
