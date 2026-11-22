// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00639470 (105 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20ddf0 (VA 0x0060DDF0, 112 bytes incl. padding)
// RA2 symbol : ?Planning_Find_Drawn@@YGPAVPlanningNodeClass@@VCoord@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9278)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

PlanningNodeClass * __stdcall Planning_Find_Drawn(Coord coord) // RA2: 0x00616210; the first drawn node whose lead order aims at the coordinate
{
	int count = PlanningNodeClass::DrawnNodes.Count(); // RA2: as above
	for (int i = 0; i < count; i++) { // RA2: as above
		PlanningNodeClass * node = PlanningNodeClass::DrawnNodes[i]; // RA2: as above
		if (node->Lead_Coord() == coord) { // RA2: as above
			return node; // RA2: as above
		}
	}
	return NULL; // RA2: as above
}
