// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063AB00 (86 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20f480 (VA 0x0060F480, 96 bytes incl. padding)
// RA2 symbol : ?Planning_Right_Release@@YGXHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8438)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __stdcall Planning_Right_Release(int x, int y) // RA2: 0x006178A0; planning mode's right button release: a click (not a drag) with nothing selected lets go of the selected node
{
	PlanningDragging = false; // RA2: as above
	if (PlanningNodeClass::PlanningModeActive && CurrentObject.Count() <= 0 && PlanningSelectedNode != NULL && abs(x - PlanningMouseDown.X) <= 3 && abs(y - PlanningMouseDown.Y) <= 3) { // RA2: as above
		PlanningSelectedNode = NULL; // RA2: as above
	}
}
