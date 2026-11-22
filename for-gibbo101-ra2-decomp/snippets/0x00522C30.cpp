// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00522C30 (44 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x108b30 (VA 0x00508B30, 48 bytes incl. padding)
// RA2 symbol : ?Is_Idle_Doing@InfantryClass@@QBE_NW4DoType@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8947)
// source TU  : src/m85/src/infantry.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: whether a Do type is an idle or cheer sequence.
/// </summary>
bool InfantryClass::Is_Idle_Doing(DoType doing) const
{
	if (doing == 9 || doing == 10 || doing == 18 || doing == 19 || doing == 23 || doing == 32) {
		return(true);
	}
	return(false);
}
