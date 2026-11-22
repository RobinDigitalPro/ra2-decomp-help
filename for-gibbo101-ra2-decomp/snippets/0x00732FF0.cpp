// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00732FF0 (365 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2ec640 (VA 0x006EC640, 368 bytes incl. padding)
// RA2 symbol : ?For_Each_Of_Type@@YIXPBDP6IXPAVTechnoClass@@H@ZH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9887)
// source TU  : src/m85/src/uicmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Applies the action to every object of a kind: those on the screen, or on the whole map after a selection by type reached over it.
/// </summary>
void __fastcall For_Each_Of_Type(char const * name, TechnoAction action, int argument) // RA2: 0x006F7800
{
	TechnoTest test = (TechnoTest)Is_Player_Alive_Unit_Of; // RA2: the same two walks as Unselect_Type, then the action for each object (a call through the pointer, the argument on the stack)
	TechnoList * list; // RA2: as above
	if (SelectAcrossMap) { // RA2: as above
		list = Collect_Technos(test, (int)name); // RA2: as above
	} else {
		list = Collect_Visible_Technos(test, (int)name); // RA2: as above
	}
	int count = list->Count(); // RA2: as above
	for (int index = 0; index < count; index++) { // RA2: as above
		action((*list)[index], argument); // RA2: as above
	}
	delete list; // RA2: as above
}
