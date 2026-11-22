// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00638840 (471 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20d1c0 (VA 0x0060D1C0, 480 bytes incl. padding)
// RA2 symbol : ?Planning_Cancel_Token@@YIXPAVTechnoClass@@@Z
// similarity : 0.9868 (very-similar, masked instruction tokens; shape 0.9712)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Cancel_Token(TechnoClass * techno) // RA2: 0x006155E0; lets go of the planning token of a techno, when it has one
{
	PlanningTokenClass * token = techno->Get_Planning_Token(); // RA2: as above
	if (token != NULL) { // RA2: as above
		token->Cancel_Owner(); // RA2: as above
	}
}
