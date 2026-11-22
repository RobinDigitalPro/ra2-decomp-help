// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063B2F0 (608 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20fc70 (VA 0x0060FC70, 608 bytes incl. padding)
// RA2 symbol : ?Planning_Draw_Remembered@@YAXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __cdecl Planning_Draw_Remembered(void) // RA2: 0x00618090; outlines the node under the mouse and the selected node in white
{
	int color = Planning_Pixel(&WhiteColor); // RA2: as above
	if (PlanningHoverNode) { // RA2: as above; level-2 1.001: implicit tests as gibbo101
		PlanningHoverNode->Frame_Lead_Box(color); // RA2: as above
	}
	if (PlanningSelectedNode) { // RA2: as above
		PlanningSelectedNode->Frame_Lead_Box_Outer(color); // RA2: as above
	}
}
