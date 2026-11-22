// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063D0F0 (288 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x211a60 (VA 0x00611A60, 288 bytes incl. padding)
// RA2 symbol : ?Planning_Techno_Color@@YIHPAVTechnoClass@@@Z
// similarity : 0.9720 (very-similar, masked instruction tokens; shape 0.9862)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __fastcall Planning_Techno_Color(TechnoClass * techno) // RA2: 0x00619E80; black, or white for a techno that is selected (or a member of the selected node)
{
	int plain = Planning_Pixel(&BlackColor); // RA2: as above
	if (techno == NULL) { // RA2: as above
		return plain; // RA2: as above
	}
	int lighter = Planning_Pixel(&WhiteColor); // RA2: as above
	if (PlanningSelectedNode != NULL) { // RA2: as above
		if (PlanningSelectedNode->Find_Member(techno) != -1) { // RA2: as above
			return lighter; // RA2: as above
		}
		return plain; // RA2: as above
	}
	if (techno->IsSelected) { // RA2: as above
		return lighter; // RA2: as above
	}
	return plain; // RA2: as above
}
