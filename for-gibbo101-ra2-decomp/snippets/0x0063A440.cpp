// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063A440 (91 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20edc0 (VA 0x0060EDC0, 96 bytes incl. padding)
// RA2 symbol : ?Planning_Event_Result@@YIHPAVPlanningTokenClass@@PBUPlanningEventTargets@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9383)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __fastcall Planning_Event_Result(PlanningTokenClass * token, PlanningEventTargets const * event) // RA2: 0x006171E0; what planning mode shows for an order: 0 for one that ends the path, 2 at the last free node, -1 for none
{
	int mission = event->CurrentMission(); // RA2: as above
	TargetClass const & target = event->Target(); // RA2: as above
	if (Planning_Terminal_Mission(mission)) { // RA2: as above
		return 0; // RA2: as above
	}
	if (Planning_Cell_Mission(mission, target)) { // RA2: as above
		return 0; // RA2: as above
	}
	if (token->Node_Count() == 15) { // RA2: as above
		return 2; // RA2: as above
	}
	return -1; // RA2: as above
}
