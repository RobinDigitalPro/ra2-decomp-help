// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063AB60 (252 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20f4e0 (VA 0x0060F4E0, 256 bytes incl. padding)
// RA2 symbol : ?Planning_Mouse_AI@@YG_NHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9785)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __stdcall Planning_Mouse_AI(int x, int y) // RA2: 0x00617900; planning mode's mouse cursor: the plain one over the picked node or when none is picked, else the small one; true when planning mode set it
{
	if (!PlanningNodeClass::PlanningModeActive) { // RA2: as above
		return false; // RA2: as above
	}
	if (PlanningDragging) { // RA2: as above
		return false; // RA2: as above
	}
	PlanningNodeClass * remembered = PlanningPickedNode; // RA2: as above
	PlanningNodeClass * node = Planning_Node_At(x, y); // RA2: as above
	if (remembered == NULL && node == NULL) { // RA2: as above
		return false; // RA2: as above
	}
	if (remembered == NULL || node == remembered) { // RA2: as above
		Map.Set_Default_Mouse(MOUSE_NORMAL, true); // RA2: as above
	} else { // RA2: as above
		Map.Set_Default_Mouse(MOUSE_NORMAL, false); // RA2: as above
	}
	return true; // RA2: as above
}
