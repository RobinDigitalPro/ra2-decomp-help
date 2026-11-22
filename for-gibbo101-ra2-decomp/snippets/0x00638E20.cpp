// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00638E20 (55 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20d7a0 (VA 0x0060D7A0, 64 bytes incl. padding)
// RA2 symbol : ?Planning_Clear_Drawn@@YAXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7805)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __cdecl Planning_Clear_Drawn(void) // RA2: 0x00615BC0; empties the list of the nodes drawn on the tactical view
{
	PlanningNodeClass::DrawnNodes.Clear(); // RA2: as above
}
