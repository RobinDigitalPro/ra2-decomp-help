// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00522CB0 (65 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x108bb0 (VA 0x00508BB0, 80 bytes incl. padding)
// RA2 symbol : ?Is_Dying@InfantryClass@@QBE_NXZ
// similarity : 0.9600 (very-similar, masked instruction tokens; shape 0.7692)
// source TU  : src/m85/src/infantry.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: whether this soldier is playing a death sequence.
/// </summary>
bool InfantryClass::Is_Dying(void) const
{
	return(Doing == 11 || Doing == 12 || Doing == 13 || Doing == 14 || Doing == 15 || Doing == 34 || Doing == 35 || Doing == 36 || Doing == 20 || Doing == 21);
}
