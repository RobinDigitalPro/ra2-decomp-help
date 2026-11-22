// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00637640 (264 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20bfc0 (VA 0x0060BFC0, 272 bytes incl. padding)
// RA2 symbol : ?Planning_Unlist_Node@@YIXPAVPlanningNodeClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9518)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Unlist_Node(PlanningNodeClass * node) // RA2: 0x006143E0
{
	PlanningNodeClass::QueuedNodes.Delete(node); // RA2: as above
	PlanningNodeClass::Unknown1.Delete(node); // RA2: as above
	PlanningNodeClass::DrawnNodes.Delete(node); // RA2: as above
	if (PlanningHoverNode == node) { // RA2: as above
		PlanningHoverNode = NULL; // RA2: as above
	}
	if (PlanningPickedNode == node) { // RA2: as above
		PlanningPickedNode = NULL; // RA2: as above
	}
	if (PlanningSelectedNode == node) { // RA2: as above
		PlanningSelectedNode = NULL; // RA2: as above
	}
}
