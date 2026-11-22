// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00639BC0 (238 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20e540 (VA 0x0060E540, 240 bytes incl. padding)
// RA2 symbol : ?Planning_Remove_Node@@YIXPAVPlanningNodeClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9901)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Remove_Node(PlanningNodeClass * node) // RA2: 0x00616960; takes a node out of the paths of its members
{
	if (node != NULL) { // RA2: as above
		TechnoClass * owner = node->PlanningMembers[0]->Owner; // RA2: as above
		PlanningNodeClass * next = node->Next_Node(owner); // RA2: as above
		for (int i = node->PlanningMembers.Count() - 1; i >= 0; i--) { // RA2: as above
			TechnoClass * member = node->PlanningMembers[i]->Owner; // RA2: as above
			PlanningTokenClass * token = member->Get_Planning_Token(); // RA2: as above
			token->Remove_Node_At(token->Node_Index(node)); // RA2: as above
		}
		if (next != NULL && next != node) { // RA2: as above
			next->Clear(); // RA2: as above
			int count = next->PlanningMembers.Count(); // RA2: as above
			for (int j = 0; j < count; j++) { // RA2: as above
				next->Assign_Branch(next->PlanningMembers[j]); // RA2: as above
			}
			next->Update_Active(); // RA2: as above
			next->Queued = false; // RA2: as above
		}
	}
}
