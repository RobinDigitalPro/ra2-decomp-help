// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063AAC0 (64 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20f440 (VA 0x0060F440, 64 bytes incl. padding)
// RA2 symbol : ?Planning_Right_Press@@YGXHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __stdcall Planning_Right_Press(int x, int y) // RA2: 0x00617860; planning mode's right button press: starts a drag, remembering the point when nothing is selected
{
	PlanningDragging = true; // RA2: as above
	PlanningMouseDown = Point2D(-1, -1); // RA2: as above
	if (PlanningNodeClass::PlanningModeActive && CurrentObject.Count() <= 0) { // RA2: as above
		PlanningMouseDown = Point2D(x, y); // RA2: as above
	}
}
