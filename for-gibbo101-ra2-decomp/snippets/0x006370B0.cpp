// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006370B0 (446 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20ba30 (VA 0x0060BA30, 448 bytes incl. padding)
// RA2 symbol : ?Planning_Reset_State@@YAXXZ
// similarity : 0.9917 (very-similar, masked instruction tokens; shape 0.9918)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __cdecl Planning_Reset_State(void) // RA2: 0x00613E50; deletes every token and clears every list and flag
{
	int count = PlanningTokenClass::Array.Count(); // RA2: as above
	PlanningTearDown = true; // RA2: as above
	PlanningNodeClass::PlanningModeActive = false; // RA2: as above
	PlanningBusy = false; // RA2: as above
	for (int i = 0; i < count; i++) { // RA2: as above
		PlanningTokenClass * token = PlanningTokenClass::Array[i]; // RA2: as above
		delete token; // RA2: as above
	}
	memset(PlanningUnitCounts, 0, sizeof(PlanningUnitCounts)); // RA2: as above
	PlanningTokenClass::Technos.Clear(); // RA2: as above
	PlanningTokenClass::Array.Clear(); // RA2: as above
	PlanningNodeClass::Unknown1.Clear(); // RA2: as above
	PlanningNodeClass::DrawnNodes.Clear(); // RA2: as above
	PlanningHoverNode = NULL; // RA2: as above
	PlanningCommandFlag = false; // RA2: as above
	PlanningLoopClosed = false; // RA2: as above
	PlanningBlockedNode = 0; // RA2: as above
	PlanningRefusalShown = false; // RA2: as above
	PlanningTearDown = false; // RA2: as above
	PlanningPendingRefusal = -1; // RA2: as above
	memset(PlanningHelpCounts, 0, sizeof(PlanningHelpCounts)); // RA2: as above
}
