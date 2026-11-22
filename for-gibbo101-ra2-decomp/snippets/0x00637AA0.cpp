// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00637AA0 (6 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20c420 (VA 0x0060C420, 16 bytes incl. padding)
// RA2 symbol : ?Planning_Is_Active@@YI_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.2857)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool Planning_Is_Active(void) // RA2: 0x00614840
{
	return PlanningNodeClass::PlanningModeActive; // RA2: as above
}
