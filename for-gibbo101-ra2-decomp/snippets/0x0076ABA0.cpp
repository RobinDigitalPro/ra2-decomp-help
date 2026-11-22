// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0076ABA0 (60 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x320a70 (VA 0x00720A70, 64 bytes incl. padding)
// RA2 symbol : ?Create@WDTState@@SI?AV?$rc_ptr@VWDTState@@@@PAX@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9259)
// source TU  : src/m85/src/wdtnet.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Fetches the game options this territory is fought under.
/// This routine is used to set up the rules for the conflict over this territory. Options
/// the tour never varies are forced to their tour values rather than taken from the
/// territory.
/// </summary>
/// <returns>Returns with a newly allocated option block. The caller is responsible for
/// deleting it.</returns>
/// <param name="data">The raw packet received from the ladder server.</param>
/// <returns>The counted pointer to the new state.</returns>
rc_ptr<WDTState> __fastcall WDTState::Create(void *data) // RA2: 0x0072BEB0; no such routine in TibSun
{
	return(rc_ptr<WDTState>(new WDTState(data))); // RA2: as above
}
