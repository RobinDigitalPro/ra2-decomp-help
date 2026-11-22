// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00634B20 (407 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2094c0 (VA 0x006094C0, 416 bytes incl. padding)
// RA2 symbol : ?Dump@PlanningNodeClass@@QAEXXZ
// similarity : 0.9860 (very-similar, masked instruction tokens; shape 0.9695)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void PlanningNodeClass::Dump(void) // RA2: 0x006118E0
{
	int branch_count = PlanningBranches.Count(); // RA2: as above
	for (int branch_index = 0; branch_index < branch_count; ++branch_index) { // RA2: as above
		PlanningBranchClass * branch = PlanningBranches[branch_index]; // RA2: as above
		int count = branch->Get_Count(); // RA2: as above
		EventClass event = branch->Get_Event(); // RA2: as above
		Coord origin = Planning_Event_Coord(event); // RA2: as above
		DebugString("Branch [%d];  Member count[%d];  Origin event location[%d, %d, %d]\n", // RA2: as above
			branch_index, count, origin.X, origin.Y, origin.Z); // RA2: as above
		int member_count = PlanningMembers.Count(); // RA2: as above
		for (int member_index = 0; member_index < member_count; ++member_index) { // RA2: as above
			PlanningMemberClass * member = PlanningMembers[member_index]; // RA2: as above
			if (member->Get_Branch() == branch_index) { // RA2: as above
				TechnoClass * owner = member->Get_Owner(); // RA2: as above
				char const * name = owner->Class_Of()->IniName; // RA2: as above
				Cell cell = owner->Get_Cell(); // RA2: as above
				DebugString("  Member [%s];  Cell location[%d, %d]\n", name, cell.X, cell.Y); // RA2: as above
			}
		}
	}
	int count = LoopBranch.Get_Count(); // RA2: as above
	if (count > 0) { // RA2: as above
		EventClass event = LoopBranch.Get_Event(); // RA2: as above
		Coord origin = Planning_Event_Coord(event); // RA2: as above
		DebugString("Loop Branch [%d];  Member count[%d];  Origin event location[%d, %d, %d]\n", // RA2: as above
			LoopBranchIndex, count, origin.X, origin.Y, origin.Z); // RA2: as above
		int member_count = PlanningMembers.Count(); // RA2: as above
		for (int member_index = 0; member_index < member_count; ++member_index) { // RA2: as above
			PlanningMemberClass * member = PlanningMembers[member_index]; // RA2: as above
			if (member->Get_Active()) { // RA2: as above
				TechnoClass * owner = member->Get_Owner(); // RA2: as above
				char const * name = owner->Class_Of()->IniName; // RA2: as above
				Cell cell = owner->Get_Cell(); // RA2: as above
				DebugString("  Member [%s];  Cell location[%d, %d]\n", name, cell.X, cell.Y); // RA2: as above
			}
		}
	}
}
