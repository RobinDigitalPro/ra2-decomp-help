// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00637DB0 (20 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20c730 (VA 0x0060C730, 32 bytes incl. padding)
// RA2 symbol : ?Planning_Allows_Event_Type@@YI_NH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6000)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Planning_Allows_Event_Type(int type) // RA2: 0x00614B50; whether an event type may be sent now: no mission events while planning mode is on
{
	if (PlanningNodeClass::PlanningModeActive && type == 4) { // RA2: as above
		return false; // RA2: as above
	}
	return true; // RA2: as above
}
