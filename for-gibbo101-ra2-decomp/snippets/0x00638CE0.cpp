// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00638CE0 (221 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20d660 (VA 0x0060D660, 224 bytes incl. padding)
// RA2 symbol : ?Planning_Order_Kind@@YIHPAVTechnoClass@@PBUPlanningEventTargets@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9840)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __fastcall Planning_Order_Kind(TechnoClass * techno, PlanningEventTargets const * event) // RA2: 0x00615A80; how an order relates to the path of the techno: 0 refused outright, 1 and 2 past a terminating or a continual order, -1 taken
{
	if (Planning_Stop_Type(event->Type)) { // RA2: as above
		return 0; // RA2: as above
	}
	int order_mission = event->CurrentMission(); // RA2: as above
	TargetClass const & target = event->Target(); // RA2: as above
	if (Planning_Order_Stays_Put(techno, order_mission, target)) { // RA2: as above
		return 0; // RA2: as above
	}
	PlanningTokenClass * token = techno->Get_Planning_Token(); // RA2: as above
	if (token != NULL && token->Node_Count() > 0) { // RA2: as above
		EventClass last_event = token->Event_At(token->Node_Count() - 1); // RA2: as above
		PlanningEventTargets const * targets = (PlanningEventTargets const *)&last_event; // RA2: as above
		if (Planning_Terminal_Mission(targets->CurrentMission())) { // RA2: as above
			return 1; // RA2: as above
		}
		if (Planning_Cell_Mission(targets->CurrentMission(), targets->Target())) { // RA2: as above
			return 2; // RA2: as above
		}
	}
	return -1; // RA2: as above
}
