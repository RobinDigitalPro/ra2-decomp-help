// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00638F90 (173 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20d910 (VA 0x0060D910, 176 bytes incl. padding)
// RA2 symbol : ?Planning_Node_At@@YGPAVPlanningNodeClass@@HH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9756)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

PlanningNodeClass * __stdcall Planning_Node_At(int x, int y) // RA2: 0x00615D30; the node under the mouse when the point is inside its box
{
	return Planning_Hit_Node(PlanningHoverNode, x, y); // level-2 1.001: through the helper (matches 0x20d910 and its inlined copy in Planning_Mouse_AI 0x20f4e0) // RA2: as above
}
