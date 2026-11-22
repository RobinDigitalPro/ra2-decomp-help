// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063B150 (411 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20fad0 (VA 0x0060FAD0, 416 bytes incl. padding)
// RA2 symbol : ?Planning_Draw_All@@YAXXZ
// similarity : 0.9776 (very-similar, masked instruction tokens; shape 0.9817)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __cdecl Planning_Draw_All(void) // RA2: 0x00617EF0; draws the filled version of the nodes and the paths of the technos that are allies of the player
{
	int count = PlanningNodeClass::Unknown1.Count(); // RA2: as above
	int i; // RA2: as above
	for (i = 0; i < count; i++) { // RA2: as above
		PlanningNodeClass * node = PlanningNodeClass::Unknown1[i]; // RA2: as above
		if (node->Lead_House()->Is_Ally(PlayerPtr)) { // RA2: as above
			Planning_Draw_Filled_Node(node); // RA2: as above
		}
	}
	for (i = 0; i < count; i++) { // RA2: as above
		PlanningNodeClass * node = PlanningNodeClass::Unknown1[i]; // RA2: as above
		if (node->Lead_House()->Is_Ally(PlayerPtr)) { // RA2: as above
			node->Fill_Lead_Box(node->Node_Color()); // RA2: as above
		}
	}
	int technos = Technos.Count(); // RA2: as above
	for (i = 0; i < technos; i++) { // RA2: as above
		TechnoClass * techno = Technos[i]; // RA2: as above
		if (techno->House->Is_Ally(PlayerPtr)) { // RA2: as above
			Planning_Draw_Filled_Techno(techno); // RA2: as above
		}
	}
}
