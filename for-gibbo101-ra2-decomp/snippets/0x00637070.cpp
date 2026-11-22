// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00637070 (46 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20b9f0 (VA 0x0060B9F0, 48 bytes incl. padding)
// RA2 symbol : ?Planning_Reset@@YAXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9167)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __cdecl Planning_Reset(void) // RA2: 0x00613E10
{
	PlanningNodeClass::PlanningModeActive = false; // RA2: as above
	PlanningTearDown = false; // RA2: as above
	PlanningHoverNode = NULL; // RA2: as above
	PlanningPickedNode = NULL; // RA2: as above
	PlanningSelectedNode = NULL; // RA2: as above
	PlanningMouseDown = Point2D(0, 0); // RA2: as above
	PlanningDragging = false; // RA2: as above
}
