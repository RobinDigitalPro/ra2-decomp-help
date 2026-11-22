// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0076AAB0 (57 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x320980 (VA 0x00720980, 64 bytes incl. padding)
// RA2 symbol : ?Create@WDTTerritory@@SI?AV?$rc_ptr@VWDTTerritory@@@@XZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8679)
// source TU  : src/m85/src/wdtnet.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Makes a new territory record, counted.
/// </summary>
/// <returns>The counted pointer to the new territory.</returns>
rc_ptr<WDTTerritory> __fastcall WDTTerritory::Create(void) // RA2: 0x0072BDC0; no such routine in TibSun, which makes its territories with new
{
	return(rc_ptr<WDTTerritory>(new WDTTerritory())); // RA2: as above
}
