// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007667E0 (6 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31c730 (VA 0x0071C730, 16 bytes incl. padding)
// RA2 symbol : ?WDT_Get_Unit_Count@@YIHPBVWDTTerritory@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.3750)
// source TU  : src/m85/src/wdtconflict.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Fetches the number of units each player starts a battle over the territory with.
/// This is the getter that the unit count game option reads its value through.
/// </summary>
/// <param name="territory">The territory to read.</param>
/// <returns>Returns with the territory's starting unit count.</returns>
int __fastcall WDT_Get_Unit_Count(WDTTerritory const * territory) // RA2: 0x00727B70, the getter of the WDT:UnitCount option
{
	return(territory->UnitCount); // RA2: as above
}
