// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00637DD0 (47 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20c750 (VA 0x0060C750, 48 bytes incl. padding)
// RA2 symbol : ?Planning_Send_Event@@YGXVEventClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9714)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __stdcall Planning_Send_Event(EventClass event) // RA2: 0x00614B70; sends a mission event marked as planned
{
	if (event.Type == EventClass::MEGAMISSION) { // RA2: as above
		event.Data.MegaMission.IsPlanningEvent = true; // RA2: as above
		Add_Outgoing_Event(event); // RA2: as above
	}
}
