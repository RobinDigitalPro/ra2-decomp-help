// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007331B0 (450 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2ec800 (VA 0x006EC800, 448 bytes incl. padding)
// RA2 symbol : ?Refresh_Type_Select_List@@YAXXZ
// similarity : 0.9691 (very-similar, masked instruction tokens; shape 0.9969)
// source TU  : src/m85/src/uicmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Makes the list a state or rank selection works on: the selected objects, or when none is a techno, the player's objects on the screen that are not buildings.
/// </summary>
void __cdecl Refresh_Type_Select_List(void) // RA2: 0x006F79C0
{
	if (TypeSelectList != NULL) { // RA2: the old list is deleted, the selected technos are collected and, when there are none, the player technos on the screen that are not buildings
		delete TypeSelectList; // RA2: as above
		TypeSelectList = NULL; // RA2: as above
	}
	TypeSelectList = Collect_Selected_Technos(); // RA2: as above
	if (TypeSelectList->Count() == 0) { // RA2: as above
		delete TypeSelectList; // RA2: as above
		TypeSelectList = NULL; // RA2: as above
		TypeSelectList = Collect_Visible_Technos((TechnoTest)Is_Selectable_Player_Techno, 0); // RA2: as above
	}
}
