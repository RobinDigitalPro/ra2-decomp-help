// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00639A50 (354 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20e3d0 (VA 0x0060E3D0, 368 bytes incl. padding)
// RA2 symbol : ?Planning_Copy_Members@@YIXPAVPlanningNodeClass@@0VEventClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9489)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Copy_Members(PlanningNodeClass * node, PlanningNodeClass * from, EventClass event) // RA2: 0x006167F0; adds every member of one node to another, each with a copy of the event aimed at its techno
{
	int count = from->PlanningMembers.Count(); // RA2: as above
	for (int i = 0; i < count; i++) { // RA2: as above
		TechnoClass * techno = from->PlanningMembers[i]->Owner; // RA2: as above
		event.Data.Target.Whom = TargetClass(techno); // RA2: as above
		PlanningMemberClass * member = new PlanningMemberClass; // RA2: as above
		member->Owner = techno; // RA2: as above
		EventClass * copy = new EventClass; // RA2: as above
		*copy = event; // RA2: as above
		member->Packet = copy; // RA2: as above
		node->PlanningMembers.Add(member); // RA2: as above
		PlanningTokenClass * token = techno->Get_Planning_Token(); // RA2: as above
		token->Add_Node(node); // RA2: as above
		node->Assign_Branch(member); // RA2: as above
	}
}
