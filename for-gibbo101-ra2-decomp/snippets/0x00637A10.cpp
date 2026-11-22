// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00637A10 (139 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20c390 (VA 0x0060C390, 144 bytes incl. padding)
// RA2 symbol : ?Planning_End@@YAXXZ
// similarity : 0.9773 (very-similar, masked instruction tokens; shape 0.9462)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __cdecl Planning_End(void) // RA2: 0x006147B0; ends planning mode: sends the commit event, sound and a notice to the sink
{
	if (PlanningNodeClass::PlanningModeActive) { // RA2: as above
		EventClass event(PlayerPtr->HeapID, EventClass::PLAN_COMMIT); // RA2: as above
		Add_Outgoing_Event(event); // RA2: as above
		PlanningHoverNode = NULL; // RA2: as above
		PlanningPickedNode = NULL; // RA2: as above
		PlanningSelectedNode = NULL; // RA2: as above
		PlanningNodeClass::PlanningModeActive = false; // RA2: as above
		VocClass::PlayGlobal(Rule->EndPlanningModeSound, 1.0f, 0x2000); // RA2: as above
		if (PlanningSink) { // RA2: as above
			PlanningSink->Unknown_Virtual_0(0x11C8, 0); // RA2: as above
		}
	}
}
