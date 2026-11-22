// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00733E10 (776 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2ed400 (VA 0x006ED400, 784 bytes incl. padding)
// RA2 symbol : ?Pick_Type_By_Cost@@YIPADABV?$DynamicVectorClass@PAVTechnoClass@@@@PBDHPAH@Z
// similarity : 0.9930 (very-similar, masked instruction tokens; shape 0.9863)
// source TU  : src/m85/src/uicmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Picks the kind of the list's objects that is worth the most but still less than the limit, or the one worth the most; returns its name in a new buffer.
/// </summary>
char * __fastcall Pick_Type_By_Cost(TechnoList const & objects, char const * name, int limit, int * best) // RA2: 0x006F85E0
{
	DynamicVectorClass<char const *> * names = Collect_Type_Names(objects); // RA2: the kinds of the list with what the objects of each cost (Cost_Of of the type for the house of the object, vtable offset 132)
	DynamicVectorClass<int> * costs = new DynamicVectorClass<int>(0, NULL); // RA2: the cost of the objects of each kind
	int count = names->Count(); // RA2: as above
	for (int index = 0; index < count; index++) { // RA2: as above
		costs->Add(0); // RA2: as above
	}
	int total = objects.Count(); // RA2: as above
	for (int item = 0; item < total; item++) { // RA2: as above
		TechnoClass * object = objects[item]; // RA2: as above
		char const * id = object->Class_Of()->Name(); // RA2: as above
		int found = Find_Name_Index(*names, id); // RA2: as above
		HouseClass * house = object->House; // RA2: as above
		int sum = (*costs)[found]; // RA2: as above
		int cost = ((TechnoTypeClass const *)object->Class_Of())->Cost_Of(house); // RA2: as above
		(*costs)[found] = sum + cost; // RA2: as above
	}
	*best = 0; // RA2: as above
	int pick = -1; // RA2: as above
	if (name != NULL) { // RA2: as above
		for (int entry = 0; entry < count; entry++) { // RA2: as above
			if (strcmp(name, (*names)[entry]) != 0) { // RA2: as above
				int cost = (*costs)[entry]; // RA2: as above
				if (cost < limit && cost > *best) { // RA2: as above
					*best = cost; // RA2: as above
					pick = entry; // RA2: as above
				}
			}
		}
	}
	if (name == NULL || *best == 0) { // RA2: as above
		int most = 0; // RA2: as above
		int which = -1; // RA2: as above
		for (int slot = 0; slot < count; slot++) { // RA2: as above
			if ((*costs)[slot] > most) { // RA2: as above
				most = (*costs)[slot]; // RA2: as above
				which = slot; // RA2: as above
			}
		}
		*best = most; // RA2: as above
		pick = which; // RA2: as above
	}
	char const * selected = name; // RA2: as above
	if (pick != -1) { // RA2: as above
		selected = (*names)[pick]; // RA2: as above
	}
	char * result = new char[100]; // RA2: as above
	if (selected != NULL) { // RA2: as above
		strcpy(result, selected); // RA2: as above
	}
	delete names; // RA2: as above
	delete costs; // RA2: as above
	return result; // RA2: as above
}
