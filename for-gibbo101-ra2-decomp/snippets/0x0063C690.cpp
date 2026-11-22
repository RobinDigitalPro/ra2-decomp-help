// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063C690 (994 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x211000 (VA 0x00611000, 1008 bytes incl. padding)
// RA2 symbol : ?Planning_Draw_Node@@YIXPAVPlanningNodeClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9773)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Draw_Node(PlanningNodeClass * node) // RA2: 0x00619420; draws the lines from the nodes before this one (and from its own loop) to it as solid lines, and its box
{
	// level-2 1.001: the node accessors (Get_Count, Lead_Color, Branch_Count, Branch_Coord, Get_Branch,
	// Loop_Event) and the event pointer passed directly, as gibbo101/ra2-decomp src/planmgr.cpp
	// FUN_0063C690 (YR 0x0063C690), @719fcc7.
	Point2D pixel = node->Lead_Pixel(); // RA2: as above
	int frame = -1; // RA2: as above
	if (node->Get_Count() > 0) { // RA2: as above
		EventClass event = node->Get_Event(0); // RA2: as above
		frame = ((PlanningFirstTarget &)event).Get_Event_Frame(); // RA2: as above
	}
	int color = node->Lead_Color(); // RA2: as above
	int count = node->Branch_Count(); // RA2: as above
	for (int index = 0; index < count; index++) { // RA2: as above
		Coord coord = node->Branch_Coord(index); // RA2: as above
		Point2D start = Planning_Coord_Pixel(coord); // RA2: as above
		if (coord == Coord(-1, -1, -1)) { // RA2: as above
			PlanningBranchClass * branch = node->Get_Branch(index); // RA2: as above
			start = Planning_Event_Pixel(&branch->Event, node->Owner_At_Branch(index)); // RA2: as above
		}
		Planning_Draw_Thick_Line(start, pixel, 4, color); // RA2: as above
		if (frame != -1) { // RA2: as above
			Planning_Draw_Midpoint(start, pixel, color); // RA2: as above
		}
	}
	if (node->Is_Loop_Alone()) { // RA2: as above
		Coord coord = node->Loop_Coord(); // RA2: as above
		Point2D start = Planning_Coord_Pixel(coord); // RA2: as above
		if (coord == Coord(-1, -1, -1)) { // RA2: as above
			start = Planning_Event_Pixel(node->Loop_Event(), node->Active_Owner()); // RA2: as above
		}
		Planning_Draw_Thick_Line(start, pixel, 4, color); // RA2: as above
		if (frame != -1) { // RA2: as above
			Planning_Draw_Midpoint(start, pixel, color); // RA2: as above
		}
	}
	node->Draw_Lead_Box(color); // RA2: as above
}
