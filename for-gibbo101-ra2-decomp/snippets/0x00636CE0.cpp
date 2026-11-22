// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00636CE0 (176 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20b660 (VA 0x0060B660, 176 bytes incl. padding)
// RA2 symbol : ?Reset_Node_Colors@PlanningTokenClass@@QAEXXZ
// similarity : 0.9701 (very-similar, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void PlanningTokenClass::Reset_Node_Colors(void) // RA2: 0x00613A80
{
	if (F98) { // RA2: as above
		PlanningNodeClass * node = Loop_Node(); // RA2: as above
		if (node != NULL) node->Reset_Colors(true); // RA2: as above
		F98 = false; // RA2: as above
	}
	int start = F8C == -1 ? 0 : F8C; // RA2: as above
	int count = PlanningNodes.Count(); // RA2: as above
	for (int index = start; index < count; index++) { // RA2: as above
		PlanningNodeClass * node = PlanningNodes[index]; // RA2: as above
		if (node != NULL) node->Reset_Colors(true); // RA2: as above
	}
	F8C = -1; // RA2: as above
}
