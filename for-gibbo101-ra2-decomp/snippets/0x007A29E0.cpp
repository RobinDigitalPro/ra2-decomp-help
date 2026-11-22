// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007A29E0 (1167 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x34a3f0 (VA 0x0074A3F0, 1152 bytes incl. padding)
// RA2 symbol : ?WOL_Add_Opponent_Dialog_Proc@@YGHPAUHWND__@@IIJ@Z
// similarity : 0.9700 (very-similar, masked instruction tokens; shape 0.9858)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

BOOL CALLBACK WOL_Add_Opponent_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) // RA2: 1.001 0x0074A3F0, the dialog (0x122) that offers the opponent of the quick match as a buddy; the check box 0x6F9 stops asking
{
	if (message == WM_INITDIALOG && lparam) {
		SetWindowLong(window, 8, ((int *)lparam)[1]);
	}
	int result = Standard_Dialog_Proc(window, message, wparam, lparam);
	if (result) {
		return(result);
	}
	OwnerDraw::SimpleDialogControl * control = (OwnerDraw::SimpleDialogControl *)GetWindowLong(window, 8);
	switch (message) {
	case WM_ERASEBKGND:
		return(TRUE);

	case WM_PAINT:
		Dialog_On_WM_PAINT(window);
		Slide_Pending_Dialog(window);
		ValidateRect(window, NULL);
		return(TRUE);

	case WM_DRAWITEM:
		Dialog_On_WM_DRAWITEM(lparam);
		return(TRUE);

	case 0x497:
		{
			wchar_t text[128];
			swprintf(text, L"Add %hs to your buddy list?", g_MatchOpponentName.get());
			HWND label = GetDlgItem(window, 0x71B);
			SendMessage(label, OD_SETLABEL, 0, (LPARAM)text);
		}
		return(FALSE);

	case WM_COMMAND:
		switch (LOWORD(wparam)) {
		case IDOK:
			{
				bool checked = IsDlgButtonChecked(window, 0x6F9) == BST_CHECKED;
				Set_Add_Match_Buddies(!checked);
			}
			Add_Buddy(g_MatchOpponentName);
			control->Set_Window((unsigned int)window, (HWND)1);
			break;

		case IDCANCEL:
			{
				bool checked = IsDlgButtonChecked(window, 0x6F9) == BST_CHECKED;
				Set_Add_Match_Buddies(!checked);
			}
			control->Set_Window((unsigned int)window, (HWND)2);
			return(FALSE);
		}
		break;
	}
	return(FALSE);
}
