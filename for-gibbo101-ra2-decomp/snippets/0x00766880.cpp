// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00766880 (98 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31c7d0 (VA 0x0071C7D0, 112 bytes incl. padding)
// RA2 symbol : ?Create@?$ValueGameOption@E@WorldDominationTour@@SI?AV?$rc_ptr@V?$ValueGameOption@E@WorldDominationTour@@@@IP6IHPBVWDTTerritory@@@ZVWstring@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8478)
// source TU  : src/m85/src/wdtconflict.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Creates a counted conflict over the specified territory.
/// A conflict is the campaign's record of a battle still to be fought. The territory is
/// what supplies the map and the game options when the player finally commits to it.
/// </summary>
/// <param name="terr">The territory to be fought over. May be empty, which leaves the
/// conflict as a placeholder with no battle attached to it.</param>
/// <returns>Returns with the new conflict.</returns>
rc_ptr<Conflict> __fastcall Conflict::Create(rc_ptr<WDTTerritory> const & terr) // RA2: a counted conflict made over a counted territory (0x007272F0)
{
	return(rc_ptr<Conflict>(new Conflict(terr))); // RA2: as above
}
