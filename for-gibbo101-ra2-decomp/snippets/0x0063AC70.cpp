// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063AC70 (182 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20f5f0 (VA 0x0060F5F0, 192 bytes incl. padding)
// RA2 symbol : ?Planning_Selection_Node_State@@YIHPAVPlanningNodeClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9412)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __fastcall Planning_Selection_Node_State(PlanningNodeClass * node) // RA2: 0x00617A10; how the selected objects relate to a node: 1 for an object whose path has closed a loop, 5 for one whose path lacks the node, 2 and 3 for the last and the second last node of a path, -1 for none
{
	int count = CurrentObject.Count(); // RA2: as above
	for (int i = 0; i < count; i++) { // RA2: as above
		ObjectClass * object = CurrentObject[i]; // RA2: as above
		bool techno; // RA2: as above
		if (object != NULL) { // RA2: as above
			techno = object->AbstractFlags & 1; // RA2: as above
		}
		if (object != NULL && techno) { // RA2: as above
			PlanningTokenClass * token = ((TechnoClass *)object)->Get_Planning_Token(); // RA2: as above
			if (token != NULL) { // RA2: as above
				if (Planning_Token_Looped(token)) { // RA2: as above
					return 1; // RA2: as above
				}
				int index = token->Node_Index(node); // RA2: as above
				if (index == -1) { // RA2: as above
					return 5; // RA2: as above
				}
				if (index == token->PlanningNodes.Count() - 1) { // RA2: as above
					return 2; // RA2: as above
				}
				if (index == token->PlanningNodes.Count() - 2) { // RA2: as above
					return 3; // RA2: as above
				}
			}
		}
	}
	return -1; // RA2: as above
}
