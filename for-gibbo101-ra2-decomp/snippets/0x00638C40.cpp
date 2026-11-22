// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00638C40 (42 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20d5c0 (VA 0x0060D5C0, 48 bytes incl. padding)
// RA2 symbol : ?Planning_Cell_Mission@@YI_NHVTargetClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8500)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Planning_Cell_Mission(int mission, TargetClass target) // RA2: 0x006159E0; an attack or an area guard aimed at a cell, or for the area guard at nothing
{
	if (mission == 1 || mission == 11) { // RA2: as above
		if (RTTIType(target) == RTTI_CELL) { // RA2: as above
			return true; // RA2: as above
		}
		if (mission == 11 && !target.Is_Valid()) { // RA2: as above
			return true; // RA2: as above
		}
	}
	return false; // RA2: as above
}
