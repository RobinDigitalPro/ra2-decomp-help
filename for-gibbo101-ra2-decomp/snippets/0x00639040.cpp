// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00639040 (229 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20d9c0 (VA 0x0060D9C0, 240 bytes incl. padding)
// RA2 symbol : ?Is_Planning_Selection_Valid@@YI_NXZ
// similarity : 0.9659 (very-similar, masked instruction tokens; shape 0.9412)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Is_Planning_Selection_Valid(void) // RA2: 0x00615DE0; whether planning mode accepts the selected objects: every selected techno has a path that ends at a node of the same members; level-2 1.001: gibbo101/ra2-decomp src/planmgr.cpp FUN_00639040 (@719fcc7) form, goto fail after the loops
{
	if (!PlanningNodeClass::PlanningModeActive) { // RA2: as above
		return true; // RA2: as above
	}
	int count = CurrentObject.Count(); // RA2: as above
	if (count == 0) { // RA2: as above
		return true; // RA2: as above
	}
	int i; // RA2: as above
	for (i = 0; i < count; i++) { // RA2: as above
		ObjectClass * object = CurrentObject[i]; // RA2: as above
		if (Planning_Is_Techno(object)) { // RA2: as above
			PlanningTokenClass * first = ((TechnoClass *)object)->Get_Planning_Token(); // RA2: as above
			for (i = 0; i < count; i++) { // RA2: as above
				ObjectClass * other = CurrentObject[i]; // RA2: as above
				if (!Planning_Is_Techno(other)) goto fail; // RA2: as above
				PlanningTokenClass * token = ((TechnoClass *)other)->Get_Planning_Token(); // RA2: as above
				if (!Planning_Same_Last_Node(first, token)) goto fail; // RA2: as above
			}
			return true; // RA2: as above
		}
	}
	return false; // RA2: as above
fail:
	Planning_Refuse("MSG:PlanningModeHeteroSel"); // RA2: as above
	return false; // RA2: as above
}
