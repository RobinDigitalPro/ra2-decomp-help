// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063CAE0 (852 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x211450 (VA 0x00611450, 864 bytes incl. padding)
// RA2 symbol : ?Planning_Draw_Filled_Node@@YIXPAVPlanningNodeClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9786)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Draw_Filled_Node(PlanningNodeClass * node) // RA2: 0x00619870; draws the lines from the nodes before this one (and from its own loop) to it as dashed lines, and fills its box
{
	// level-2 1.001: the node accessors (Get_Count, Lead_Color, Branch_Count, Branch_Coord, Get_Branch,
	// Loop_Event) and the event pointer passed directly, as gibbo101/ra2-decomp src/planmgr.cpp
	// FUN_0063CAE0 (YR 0x0063CAE0), @719fcc7.
	Point2D pixel = node->Lead_Pixel(); // RA2: as above
	int frame = -1; // RA2: as above
	if (node->Get_Count() > 0) { // RA2: as above
		EventClass event = node->Get_Event(0); // RA2: as above
		frame = ((PlanningFirstTarget &)event).Get_Event_Frame(); // RA2: as above
	}
	int fill = node->Lead_Color(); // RA2: as above
	int count = node->Branch_Count(); // RA2: as above
	for (int i = 0; i < count; i++) { // RA2: as above
		int color = node->Branch_Color(i); // RA2: as above
		Coord coord = node->Branch_Coord(i); // RA2: as above
		Point2D source = Planning_Coord_Pixel(coord); // RA2: as above
		if (coord == Coord(-1, -1, -1)) { // RA2: as above
			PlanningBranchClass * branch = node->Get_Branch(i); // RA2: as above
			TechnoClass * owner = node->Owner_At_Branch(i); // RA2: as above
			source = Planning_Event_Pixel(&branch->Event, owner); // RA2: as above
		}
		Planning_Draw_Dashed_Thick_Line(source, pixel, 4, color); // RA2: as above
		if (frame != -1) { // RA2: as above
			Planning_Draw_Midpoint_Shape(source, pixel, color, fill, frame); // RA2: as above
		}
	}
	if (node->Is_Loop_Alone()) { // RA2: as above
		int color = node->Loop_Color(); // RA2: as above
		Coord coord = node->Loop_Coord(); // RA2: as above
		Point2D source = Planning_Coord_Pixel(coord); // RA2: as above
		if (coord == Coord(-1, -1, -1)) { // RA2: as above
			TechnoClass * owner = node->Active_Owner(); // RA2: as above
			source = Planning_Event_Pixel(node->Loop_Event(), owner); // RA2: as above
		}
		Planning_Draw_Dashed_Thick_Line(source, pixel, 4, color); // RA2: as above
		if (frame != -1) { // RA2: as above
			Planning_Draw_Midpoint_Shape(source, pixel, color, fill, frame); // RA2: as above
		}
	}
	node->Fill_Lead_Box(node->Node_Color()); // RA2: as above
}
