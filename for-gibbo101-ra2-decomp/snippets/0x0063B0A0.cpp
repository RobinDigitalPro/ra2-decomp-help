// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063B0A0 (176 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20fa20 (VA 0x0060FA20, 176 bytes incl. padding)
// RA2 symbol : ?Planning_Redraw@@YAXXZ
// similarity : 0.9661 (very-similar, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __cdecl Planning_Redraw(void) // RA2: 0x00617E40; rebuilds the list of the drawn nodes: draws the nodes and the paths of the technos that are allies of the player
{
	Planning_Clear_Drawn(); // RA2: as above
	int count = PlanningNodeClass::Unknown1.Count(); // RA2: as above
	int i; // RA2: as above
	for (i = 0; i < count; i++) { // RA2: as above
		PlanningNodeClass * node = PlanningNodeClass::Unknown1[i]; // RA2: as above
		if (node->Lead_House()->Is_Ally(PlayerPtr)) { // RA2: as above
			Planning_Draw_Node(node); // RA2: as above
		}
	}
	count = Technos.Count(); // RA2: as above
	for (i = 0; i < count; i++) { // RA2: as above
		TechnoClass * techno = Technos[i]; // RA2: as above
		HouseClass * house = techno->House; // RA2: as above
		if (house->Is_Ally(PlayerPtr)) { // RA2: as above
			Planning_Draw_Techno(techno); // RA2: as above
		}
	}
}
