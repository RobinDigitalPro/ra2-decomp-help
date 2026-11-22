// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063A5A0 (818 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20ef20 (VA 0x0060EF20, 832 bytes incl. padding)
// RA2 symbol : ?Planning_Left_Press@@YI_NVPoint2D@@@Z
// similarity : 0.9530 (very-similar, masked instruction tokens; shape 0.9710)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Planning_Left_Press(Point2D xy) // RA2: 0x00617340; planning mode's left button press on the tactical view: takes the node under the mouse as the picked one (the path starts there), else refuses a selection or a node planning mode cannot use; true when it took the input
{
	// level-2 1.001: __fastcall with the point by value, as gibbo101/ra2-decomp src/planmgr.cpp
	// FUN_0063A5A0 (YR 0x0063A5A0, @719fcc7); planmgr.h still declares the m85 (int, int) form
	// (header proposal; scroll.cpp then calls Planning_Left_Press(point), checked byte-identical).
	// The x and y locals are INFERRED from the register choice (y in ebp, x in ebx).
	if (!PlanningNodeClass::PlanningModeActive) { // RA2: as above
		return false; // RA2: as above
	}
	int x = xy.X;
	int y = xy.Y;
	PlanningNodeClass * previous = Planning_Get_Picked_Node(); // RA2: as above
	PlanningNodeClass * node = Planning_Node_At(x, y); // RA2: as above
	if (node && node != previous) { // RA2: as above
		Map.Set_Default_Mouse(MOUSE_NORMAL, true); // RA2: as above
		Planning_Set_Picked_Node(node); // RA2: as above
	} else { // RA2: as above
		PlanningNodeClass * picked = Planning_Node_In(PlanningNodeClass::Unknown1, x, y); // RA2: as above; level-2 1.001: the list helper directly, as in Left_Release (0x20ef20 then inlines Lead_Rect in the loop like the executable)
		if (picked) { // RA2: as above
			if (Planning_Selection_Node_State(picked) != -1) { // RA2: as above
				Planning_Refuse("MSG:PlanningModeInvalidNodeX"); // RA2: as above
				return true; // RA2: as above
			}
		} else { // RA2: as above
			int kind = Planning_Selection_Kind(); // RA2: as above
			if (kind != -1) { // RA2: as above
				Planning_Refuse_Selection(kind); // RA2: as above
				return true; // RA2: as above
			}
		}
	}
	return previous || node; // RA2: as above
}
