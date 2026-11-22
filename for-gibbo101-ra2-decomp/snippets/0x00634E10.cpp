// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00634E10 (585 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2097b0 (VA 0x006097B0, 592 bytes incl. padding)
// RA2 symbol : ?Assign_Branch@PlanningNodeClass@@QAEHPAVPlanningMemberClass@@@Z
// similarity : 0.9746 (very-similar, masked instruction tokens; shape 0.9825)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int PlanningNodeClass::Assign_Branch(PlanningMemberClass * member) // RA2: 0x00611BD0
{
	TechnoClass * owner = member->Get_Owner(); // RA2: as above
	int index = Find_Branch(owner); // RA2: as above
	if (index == -1) { // RA2: as above
		PlanningNodeClass * previous = Prev_Node(owner); // RA2: as above
		PlanningNodeClass * last = owner->Get_Planning_Token()->Last_Node(); // RA2: as above
		if (previous == last) { // RA2: as above
			member->Set_Branch(-1); // RA2: as above
			return -1; // RA2: as above
		}
		EventClass event = previous->Get_Event_For(owner); // RA2: as above
		PlanningBranchClass * branch = new PlanningBranchClass; // RA2: as above
		branch->Set_Event(event); // RA2: as above
		branch->Inc_Count(); // RA2: as above
		PlanningBranches.Add(branch); // RA2: as above
		int count = PlanningBranches.Count() - 1; // RA2: as above
		if (Is_Loop_Alone()) { // RA2: as above
			Find_Loop_Branch(this); // RA2: as above
		}
		Reset_Colors(false); // RA2: as above
		member->Set_Branch(count); // RA2: as above
		return count; // RA2: as above
	} else { // RA2: as above
		PlanningBranchClass * branch = PlanningBranches[index]; // RA2: as above
		branch->Set_Color(-1); // RA2: as above
		Reset_Colors(false); // RA2: as above
		branch->Inc_Count(); // RA2: as above
		member->Set_Branch(index); // RA2: as above
		return index; // RA2: as above
	}
}
