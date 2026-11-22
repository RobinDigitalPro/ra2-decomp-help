// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00639E30 (291 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20e7b0 (VA 0x0060E7B0, 304 bytes incl. padding)
// RA2 symbol : ?Planning_Same_Last_Node@@YI_NPAVPlanningTokenClass@@0@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9556)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Planning_Same_Last_Node(PlanningTokenClass * first, PlanningTokenClass * second) // RA2: 0x00616BD0; whether both paths (or none) end at nodes holding the owners of both
{
	if (first == NULL && second == NULL) { // RA2: as above
		return true; // RA2: as above
	}
	int first_count = 0; // RA2: as above
	if (first != NULL) { // RA2: as above
		first_count = first->Node_Count(); // RA2: as above
	}
	int second_count = 0; // RA2: as above
	if (second != NULL) { // RA2: as above
		second_count = second->Node_Count(); // RA2: as above
	}
	if (first_count == 0 && second_count == 0) { // RA2: as above
		return true; // RA2: as above
	}
	if (first_count == 0 || second_count == 0) { // RA2: as above
		return false; // RA2: as above
	}
	PlanningNodeClass * first_last = first->Node_At(first_count - 1); // RA2: as above
	PlanningNodeClass * second_last = second->Node_At(second_count - 1); // RA2: as above
	TechnoClass * first_owner = first->OwnerUnit; // RA2: as above
	TechnoClass * second_owner = second->OwnerUnit; // RA2: as above
	if (!first_last->Has_Member(second_owner)) { // RA2: as above
		return false; // RA2: as above
	}
	if (!second_last->Has_Member(first_owner)) { // RA2: as above
		return false; // RA2: as above
	}
	return true; // RA2: as above
}
