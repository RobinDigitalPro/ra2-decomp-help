// ra2-decomp help snippet, update 2026-11-23 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0056D100 (290 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0x14cc50 (VA 0x0054CC50, 290 bytes without padding)
// RA2 symbol : ?Is_Same_Cell_Zone@MapClass@@QAE_NABVCell@@0W4MZoneType@@_N22@Z
// similarity : 0.8943 (similar, masked instruction tokens; shape 0.9268)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/map.cpp
// License    : GPL-3.0-or-later. Our source is GPL and contains EA GPL code (section 7 terms)
//              and code adapted from mischa85/RedAlert2 and gibbo101/ra2-decomp; their
//              credits are kept. The notice of the source file follows. See ../README.md.
// Use        : a read-only lead. RA2 layouts and names; port it and match it on your own checker.

/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2025 Electronic Arts Inc.
 * Copyright 2026 OpenTS contributors
 *
 * Contains material derived from Electronic Arts source code.
 * Modified by OpenTS contributors, 2026.
 * EA's GPLv3 Section 7 additional terms and supplemental warranty
 * disclaimers apply; see LICENSE.md.
 ******************************************************************************/

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
