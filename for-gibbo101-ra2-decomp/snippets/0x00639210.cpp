// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00639210 (187 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20db90 (VA 0x0060DB90, 192 bytes incl. padding)
// RA2 symbol : ?Planning_Find_Node@@YIPAVPlanningNodeClass@@HHUCoordStruct@@@Z
// similarity : 0.9857 (very-similar, masked instruction tokens; shape 0.9655)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

PlanningNodeClass * __fastcall Planning_Find_Node(int house, int id, CoordStruct coord) // RA2: 0x00615FB0; the planned node whose lead order aims at the coordinate (of an id and a house unless -1)
{
	int count = PlanningNodeClass::Unknown1.Count(); // level-2 1.001: the count is read once
	for (int i = 0; i < count; i++) { // RA2: as above
		PlanningNodeClass * node = PlanningNodeClass::Unknown1[i]; // RA2: as above
		if (node->Lead_Coord() == Coord(coord) && (id == -1 || id == node->Id)) { // RA2: as above
			int owner = Planning_House(node->Member_Owner(0)); // level-2 1.001: the owner's house is looked up before the house test
			if (house == -1 || house == owner) { // RA2: as above
				return node; // RA2: as above
			}
		}
	}
	return NULL; // RA2: as above
}
