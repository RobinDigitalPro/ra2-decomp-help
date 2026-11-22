// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00522C60 (67 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x108b60 (VA 0x00508B60, 80 bytes incl. padding)
// RA2 symbol : ?Is_Death_Doing@InfantryClass@@QBE_NW4DoType@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7937)
// source TU  : src/m85/src/infantry.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: whether a Do type is a death sequence.
/// </summary>
bool InfantryClass::Is_Death_Doing(DoType doing) const
{
	return(doing == 11 || doing == 12 || doing == 13 || doing == 14 || doing == 15 || doing == 34 || doing == 35 || doing == 36 || doing == 20 || doing == 21);
}
