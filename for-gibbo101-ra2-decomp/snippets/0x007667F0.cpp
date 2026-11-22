// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007667F0 (6 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31c740 (VA 0x0071C740, 16 bytes incl. padding)
// RA2 symbol : ?WDT_Get_Tech_Level@@YIHPBVWDTTerritory@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.3750)
// source TU  : src/m85/src/wdtconflict.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Fetches the tech level a battle over the territory is fought at.
/// This is the getter that the tech level game option reads its value through.
/// </summary>
/// <param name="territory">The territory to read.</param>
/// <returns>Returns with the territory's tech level.</returns>
int __fastcall WDT_Get_Tech_Level(WDTTerritory const * territory) // RA2: 0x00727B80, the getter of the WDT:TechLevel option
{
	return(territory->TechLevel); // RA2: as above
}
