// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00658640 (141 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x22bf10 (VA 0x0062BF10, 144 bytes incl. padding)
// RA2 symbol : ?Update_Diplomacy_Rows@RadarDiplomacy@@QAEXPAUHWND__@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9744)
// source TU  : src/m85/src/radar.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Fills in every row of the diplomacy dialog.
/// The houses that are controlled by a player or not passive keep their own rows; the last
/// player-controlled house and the first house then swap rows so that the local player is
/// listed first.
/// </summary>
void RadarDiplomacy::Update_Diplomacy_Rows(HWND window) // RA2: at 0x00634970
{
	int last = -1; // RA2: index of the last house the player controls
	int count = Houses.Count(); // RA2: as above
	for (int index = 0; index < count; index++) { // RA2: as above
		HouseClass * house = Houses[index]; // RA2: as above
		if (house != NULL) { // RA2: as above
			if (house->Is_Player_Control()) { // RA2: as above
				last = index; // RA2: as above
			} else if (house->Class->IsMultiplayPassive) { // RA2: as above
				continue; // RA2: as above
			}
			Update_Diplomacy_Row(window, index, house); // RA2: as above
		}
	}
	HouseClass * player = Houses[last]; // RA2: the local player's house is listed first: rows 0 and last swap their houses
	HouseClass * first = Houses[0]; // RA2: as above
	Update_Diplomacy_Row(window, 0, player); // RA2: as above
	Update_Diplomacy_Row(window, last, first); // RA2: as above
}
