// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00637550 (92 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20bed0 (VA 0x0060BED0, 96 bytes incl. padding)
// RA2 symbol : ?Planning_Free_Nodes@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9429)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Free_Nodes(void) // RA2: 0x006142F0; runs the planned events still held and frees them
{
	for (int i = PlanningTokenClass::Events.Count() - 1; i >= 0; i--) { // RA2: as above
		EventClass * event = PlanningTokenClass::Events[i]; // RA2: as above
		Enqueue_Event(event); // RA2: as above
		PlanningTokenClass::Events.Delete_Index(i); // RA2: as above
		delete event; // RA2: as above
	}
}
