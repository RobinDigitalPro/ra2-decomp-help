// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00636B50 (386 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20b4d0 (VA 0x0060B4D0, 400 bytes incl. padding)
// RA2 symbol : ?Remove_Node_At@PlanningTokenClass@@QAEXH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9489)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void PlanningTokenClass::Remove_Node_At(int index) // RA2: 0x006138F0
{
	if (PlanningNodes.Count() == 1) { // RA2: as above
		F8C = -1; // RA2: as above
	} else if (F8C > 0 && index < F8C) { // RA2: as above
		F8C--; // RA2: as above
	}
	if (StepsToClosedLoop >= 0) { // RA2: as above
		if (index < StepsToClosedLoop) { // RA2: as above
			StepsToClosedLoop--; // RA2: as above
		} else { // RA2: as above
			ClosedLoopNodeCount--; // RA2: as above
			if (ClosedLoopNodeCount < 3) { // RA2: as above
				StepsToClosedLoop = -1; // RA2: as above
				ClosedLoopNodeCount = 0; // RA2: as above
			}
		}
	}
	PlanningNodeClass * node = PlanningNodes[index]; // RA2: as above
	node->Remove_Member(OwnerUnit); // RA2: as above
	PlanningNodes.Delete_Index(index); // RA2: as above
}
