// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00637750 (85 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20c0d0 (VA 0x0060C0D0, 96 bytes incl. padding)
// RA2 symbol : ?Planning_Unlist_Token@@YIXPAVPlanningTokenClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8358)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Unlist_Token(PlanningTokenClass * token) // RA2: 0x006144F0
{
	if (!PlanningTearDown) { // RA2: as above
		PlanningTokenClass::Array.Delete(token); // RA2: as above
	}
}
