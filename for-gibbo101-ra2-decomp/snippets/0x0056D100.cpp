// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0056D100 (290 bytes; gibbo status: attempted-partial 93.5%)
// RA2 RVA    : 0x14cc50 (VA 0x0054CC50, 304 bytes incl. padding)
// RA2 symbol : ?Is_Same_Cell_Zone@MapClass@@QAE_NABVCell@@0W4MZoneType@@_N22@Z
// similarity : 0.8943 (similar, masked instruction tokens; shape 0.8769)
// source TU  : src/m85/src/map.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Determines if two cells can be reached from one another.
/// This is the reachability test the unit and AI code leans on before committing to a move.
/// Ground out beyond the local radar is given the benefit of the doubt, since nothing out
/// there has been zoned yet.
/// </summary>
/// <param name="from">The cell being moved from.</param>
/// <param name="to">The cell being moved to.</param>
/// <param name="mzone">The movement zone layer to compare in. MZONE_NONE always agrees.</param>
/// <param name="from_bridge">Should the source cell answer for the bridge above it?</param>
/// <param name="to_bridge">Should the destination cell answer for the bridge above it?</param>
/// <param name="leavemap">Should a move heading off the local radar be allowed?</param>
/// <returns>bool; Are the two cells in the same zone?</returns>
bool MapClass::Is_Same_Cell_Zone(Cell const & from, Cell const & to, MZoneType mzone, bool from_bridge, bool to_bridge, bool leavemap)
{
	if (mzone == MZONE_NONE) {
		return(true);
	}

	bool flocal = Map.In_Local_Radar(from);
	bool finradar = Map.In_Radar(from);

	if (!flocal && finradar) {
		return(true);
	}

	bool tlocal = Map.In_Local_Radar(to);
	bool tinradar = Map.In_Radar(to);

	if (leavemap && flocal && !tlocal && tinradar) {
		return(true);
	}

	return(Get_Cell_Zone(from, mzone, from_bridge) == Get_Cell_Zone(to, mzone, to_bridge));
}
