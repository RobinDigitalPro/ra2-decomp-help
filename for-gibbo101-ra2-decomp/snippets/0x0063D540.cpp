// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063D540 (28 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x211eb0 (VA 0x00611EB0, 32 bytes incl. padding)
// RA2 symbol : ?Get_Event_Frame@PlanningFirstTarget@@QBEHXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8182)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int PlanningFirstTarget::Get_Event_Frame(void) const // RA2: 0x0061A2D0
{
	int mission = (signed char)Data.MegaMission.Mission; // RA2: as above
	if (mission == MISSION_GUARD_AREA) { // RA2: as above
		return Cursor_Start_Frame_76(); // RA2: as above
	}
	if (mission == MISSION_ATTACK_MOVE) { // RA2: as above
		return Cursor_Start_Frame_77(); // RA2: as above
	}
	return -1; // RA2: as above
}
