// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006378B0 (103 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20c230 (VA 0x0060C230, 112 bytes incl. padding)
// RA2 symbol : ?Planning_Queue_Node@@YIXPAVPlanningNodeClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8861)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Queue_Node(PlanningNodeClass * node) // RA2: 0x00614650
{
	if (node && !node->Get_Queued()) { // RA2: as above
		node->Set_Queued(); // RA2: as above
		PlanningNodeClass::QueuedNodes.Add(node); // RA2: as above
	}
}
