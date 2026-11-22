// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063A8E0 (466 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20f260 (VA 0x0060F260, 480 bytes incl. padding)
// RA2 symbol : ?Planning_Left_Release@@YG_NVPoint2D@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9557)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __stdcall Planning_Left_Release(Point2D point) // RA2: 0x00617680; planning mode's left button release: connects the selected objects to the node when it is the picked one, else drops the picked node; true when it took the input
{
	if (!PlanningNodeClass::PlanningModeActive) { // RA2: as above
		return false; // RA2: as above
	}
	PlanningNodeClass * remembered = Planning_Get_Picked_Node(); // RA2: as above
	PlanningNodeClass * node = Planning_Node_At(point.X, point.Y); // RA2: as above
	if (node != NULL && node == remembered) { // RA2: as above
		Map.Set_Default_Mouse(MOUSE_NORMAL, true); // RA2: as above
		Planning_Connect_Selection(); // RA2: as above
	} else { // RA2: as above
		PlanningNodeClass * picked = Planning_Node_In(PlanningNodeClass::Unknown1, point.X, point.Y); // level-2 1.001: the list helper directly (0x20f260 matches only so) // RA2: as above
		if (picked != NULL && Planning_Selection_Node_State(picked) != -1) { // RA2: as above
			return true; // RA2: as above
		}
		Planning_Set_Picked_Node(NULL); // RA2: as above
	}
	return remembered != NULL || node != NULL; // RA2: as above
}
