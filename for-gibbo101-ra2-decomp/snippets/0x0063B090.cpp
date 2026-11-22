// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063B090 (11 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20fa10 (VA 0x0060FA10, 16 bytes incl. padding)
// RA2 symbol : ?Planning_Clear_Selected_Node@@YAXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.4444)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __cdecl Planning_Clear_Selected_Node(void) // RA2: 0x00617E30; forgets the selected node
{
	PlanningSelectedNode = NULL; // RA2: as above
}
