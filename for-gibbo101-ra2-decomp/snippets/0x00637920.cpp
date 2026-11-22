// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00637920 (148 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20c2a0 (VA 0x0060C2A0, 160 bytes incl. padding)
// RA2 symbol : ?Planning_Process_Queue@@YAXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9016)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __cdecl Planning_Process_Queue(void) // RA2: 0x006146C0
{
	int count = PlanningNodeClass::QueuedNodes.Count(); // RA2: as above
	for (int i = 0; i < count; i++) { // RA2: as above
		PlanningNodeClass * node = PlanningNodeClass::QueuedNodes[i]; // RA2: as above
		node->Rebuild(); // RA2: as above
	}
	PlanningNodeClass::QueuedNodes.Clear(); // RA2: as above
}
