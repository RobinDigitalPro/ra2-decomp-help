// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0042E800 (17 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2c080 (VA 0x0042C080, 32 bytes incl. padding)
// RA2 symbol : ?Is_Placed@BaseClass@@QBE_NH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.4000)
// source TU  : src/m85/src/base.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: has the building of the node specified been placed?
/// </summary>
bool BaseClass::Is_Placed(int index) const // RA2: at 0x42C080
{
	return(Nodes[index].Placed);
}
