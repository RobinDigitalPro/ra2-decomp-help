// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E9AA0 (125 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c3250 (VA 0x005C3250, 128 bytes incl. padding)
// RA2 symbol : ?Select_Combo_By_Data@@YIXPAUHWND__@@HH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9730)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Select_Combo_By_Data(HWND dialog, int id, int data) // RA2: 0x005C9950, not in TibSun; selects the item of a combo box that carries this data, with the box hidden while it is searched
{
	HWND combo = GetDlgItem(dialog, id); // RA2: as above
	ShowWindow(combo, SW_HIDE); // RA2: as above
	int count = SendDlgItemMessageA(dialog, id, CB_GETCOUNT, 0, 0); // RA2: as above
	for (int index = 0; index < count; index++) { // RA2: as above
		if (SendDlgItemMessageA(dialog, id, CB_GETITEMDATA, index, 0) == data) { // RA2: as above
			SendDlgItemMessageA(dialog, id, CB_SETCURSEL, index, 0); // RA2: as above
			break;
		}
	}
	ShowWindow(combo, SW_SHOW); // RA2: as above
}
