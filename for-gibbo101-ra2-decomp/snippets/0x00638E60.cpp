// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00638E60 (294 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20d7e0 (VA 0x0060D7E0, 304 bytes incl. padding)
// RA2 symbol : ?Planning_Hover@@YAXXZ
// similarity : 0.9899 (very-similar, masked instruction tokens; shape 0.9519)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __cdecl Planning_Hover(void) // RA2: 0x00615C00; the planning mode's mouse hover: the drawn node under the mouse, unless it is not the player's to use
{
	if (PlanningDragging) { // RA2: as above
		return; // RA2: as above
	}
	int x = MouseCursor->Get_Mouse_X(); // RA2: as above
	int y = MouseCursor->Get_Mouse_Y(); // RA2: as above
	PlanningNodeClass * node = Planning_Node_In(PlanningNodeClass::DrawnNodes, x, y); // level-2 1.001: the list helper directly (0x20d7e0 matches only so) // RA2: as above
	if (node != PlanningHoverNode) { // RA2: as above
		PlanningBlockedNode = 0; // RA2: as above
		if (node != NULL) { // RA2: as above
			if (node->Member_Owner(0)->House != PlayerPtr || (PlanningPickedNode != NULL && PlanningPickedNode != node) || Planning_Selection_Node_State(node) != -1) { // RA2: as above
				PlanningBlockedNode = (int)node; // RA2: as above
				node = NULL; // RA2: as above
			}
		}
		PlanningHoverNode = node; // RA2: as above
		if (node != NULL) { // RA2: as above
			node->Dump(); // RA2: as above
		}
	}
}
