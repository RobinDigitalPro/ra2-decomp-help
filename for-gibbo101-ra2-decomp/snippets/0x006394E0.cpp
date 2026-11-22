// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006394E0 (193 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20de60 (VA 0x0060DE60, 208 bytes incl. padding)
// RA2 symbol : ?Planning_Send_Pair@@YIXPAVAbstractClass@@PAVPlanningNodeClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8993)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Send_Pair(AbstractClass * source, PlanningNodeClass * node) // RA2: 0x00616280; asks all players to connect the object to the node of the target the first order of the node points at
{
	EventClass event = node->Get_Event(0); // RA2: as above
	AbstractClass * object = ((PlanningFirstTarget *)&event)->First_Target_Object(); // RA2: as above
	if (object) { // RA2: as above
		EventClass pair(PlayerPtr->HeapID, EventClass::PLAN_CONNECT, TargetClass(source), TargetClass(object)); // RA2: as above
		Add_Outgoing_Event(pair); // RA2: as above
	}
}
