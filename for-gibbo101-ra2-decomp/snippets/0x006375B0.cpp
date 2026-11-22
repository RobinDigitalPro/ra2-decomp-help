// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006375B0 (139 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20bf30 (VA 0x0060BF30, 144 bytes incl. padding)
// RA2 symbol : ?Planning_Store_Event@@YIXABVEventClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9541)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Store_Event(EventClass const & source) // RA2: 0x00614350
{
	EventClass * event = new EventClass; // RA2: as above
	*event = source;
	if (event->Type == EventClass::MEGAMISSION) { // RA2: as above
		event->Data.MegaMission.IsPlanningEvent = 2; // RA2: as above
	}
	PlanningTokenClass::Events.Add(event); // RA2: as above
}
