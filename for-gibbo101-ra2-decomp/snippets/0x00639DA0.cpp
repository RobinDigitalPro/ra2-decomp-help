// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00639DA0 (131 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20e720 (VA 0x0060E720, 144 bytes incl. padding)
// RA2 symbol : ?Planning_Selection_Kind@@YAHXZ
// similarity : 0.9851 (very-similar, masked instruction tokens; shape 0.9116)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __cdecl Planning_Selection_Kind(void) // RA2: 0x00616B40; what the selected technos have in common: -1 for none that cannot use a waypoint, else the kind of the first of them
{
	int kind = -1; // RA2: as above
	int count = CurrentObject.Count(); // RA2: as above
	for (int i = 0; i < count; i++) { // RA2: as above
		ObjectClass * object = CurrentObject[i]; // RA2: as above
		bool techno; // RA2: as above
		if (object != NULL) { // RA2: as above
			techno = object->AbstractFlags & 1; // RA2: as above
		}
		TechnoClass * candidate = (object != NULL && techno) ? (TechnoClass *)object : NULL; // RA2: as above
		if (candidate == NULL || !candidate->CanUseWaypoint()) { // RA2: as above
			if (candidate != NULL && candidate->Fetch_RTTI() == RTTI_AIRCRAFT) { // RA2: as above
				kind = 0; // RA2: as above
			} else if (candidate != NULL && candidate->Fetch_RTTI() == RTTI_BUILDING) { // RA2: as above
				kind = 1; // RA2: as above
			} else { // RA2: as above
				kind = 2; // RA2: as above
			}
			break; // RA2: as above
		}
	}
	return kind; // RA2: as above
}
