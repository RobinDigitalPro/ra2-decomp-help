// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00452940 (158 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x4d830 (VA 0x0044D830, 160 bytes incl. padding)
// RA2 symbol : ?Is_Cell_In_Psychic_Range@BuildingClass@@QAE_NPBVCellClass@@@Z
// similarity : 0.9667 (very-similar, masked instruction tokens; shape 0.9836)
// source TU  : src/m85/src/building.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Is the cell within this building's psychic detection radius?
/// </summary>
bool BuildingClass::Is_Cell_In_Psychic_Range(CellClass const * cell) // RA2: not in TibSun, at 0x44DB40
{
	Coord a = Center_Coord();
	Coord b = cell->Cell_Coord();
	return(a.Distance_To(b) <= Class->PsychicDetectionRadius << 8);
}
