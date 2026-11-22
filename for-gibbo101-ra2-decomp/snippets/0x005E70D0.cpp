// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E70D0 (133 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c11f0 (VA 0x005C11F0, 144 bytes incl. padding)
// RA2 symbol : ?Select_List_Item_By_Data@@YIHPAUHWND__@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9120)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Selects the item of the map list that carries the given data.
/// The list is searched for the item whose data is the pointer, highlighted and scrolled to.
/// </summary>
/// <param name="dialog">The map dialog.</param>
/// <param name="data">The item data to look for, the MultiMission of the map.</param>
/// <returns>Returns with the index of the item, 0 if no item has the data, -1 without data.</returns>
int __fastcall Select_List_Item_By_Data(HWND dialog, int data) // RA2: 0x005C7160, not in TibSun
{
	if (data == 0) { // RA2: as above
		return(-1); // RA2: as above
	}
	int found = 0; // RA2: as above
	int count = SendDlgItemMessage(dialog, IDC_AILEVEL_SLIDER, LB_GETCOUNT, 0, 0); // RA2: as above
	for (int i = 0; i < count; i++) { // RA2: as above
		if (SendDlgItemMessage(dialog, IDC_AILEVEL_SLIDER, LB_GETITEMDATA, i, 0) == data) { // RA2: as above
			found = i; // RA2: as above
		}
	}
	SendDlgItemMessage(dialog, IDC_AILEVEL_SLIDER, LB_SETCURSEL, found, 0); // RA2: as above
	SendDlgItemMessage(dialog, IDC_AILEVEL_SLIDER, LB_SETTOPINDEX, found, 0); // RA2: as above
	return(found); // RA2: as above
}
