// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063CE40 (205 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2117b0 (VA 0x006117B0, 208 bytes incl. padding)
// RA2 symbol : ?Planning_Fill_Node@@YIXPAVPlanningNodeClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9774)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Fill_Node(PlanningNodeClass * node) // RA2: 0x00619BD0; fills the box of a node in its color
{
	node->Fill_Lead_Box(node->Node_Color()); // RA2: as above
}
