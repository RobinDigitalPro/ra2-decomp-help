// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0079D720 (877 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x345b40 (VA 0x00745B40, 880 bytes incl. padding)
// RA2 symbol : ?WOL_Page_Buddy_Dialog_Proc@@YGHPAUHWND__@@IIJ@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9943)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

BOOL CALLBACK WOL_Page_Buddy_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) // RA2: 1.001 0x00745B40, a page dialog to the selected buddy (no caller in 1.001)
{
	int result = Standard_Dialog_Proc(window, message, wparam, lparam);
	if (result) {
		return(result);
	}
	switch (message) {
	case WM_DESTROY:
		return(FALSE);

	case WM_COMMAND:
		switch (LOWORD(wparam)) {
		case 0x540:
			switch (HIWORD(wparam)) {
			case EN_CHANGE:
				{
					WideWstring text;
					Get_Control_Wide_Text((HWND)lparam, text);
					EnableWindow(GetDlgItem(window, 0x5C2), text.length() > 0);
				}
				return(FALSE);

			case EN_UPDATE:
				{
					WideWstring text;
					Get_Control_Wide_Text((HWND)lparam, text);
					text.trimTrailing(L"\n\r");
				}
				return(FALSE);

			case EN_MAXTEXT:
				SendMessage(GetDlgItem(window, 0x5C2), BM_CLICK, 0, 0);
				return(FALSE);
			}
			return(FALSE);

		case 0x5C2:
			{
				WideWstring text;
				HWND edit = GetDlgItem(window, 0x540);
				Get_Control_Wide_Text(edit, text);
				SendMessage(edit, OD_SETLABEL, 0, (LPARAM)EmptyUIName);
				if (text.length() > 0) {
					text.trimTrailing(L"\n\r");
					User user;
					memset(&user, 0, sizeof(user));
					strcpy((char *)user.name, g_SelectedBuddy.get());
					g_pChat->Unknown_Virtual_F8(&user, text.get()); // RA2: the wide page request (YR: RequestUnicodePage)
				}
				InvalidateRect(edit, NULL, FALSE);
				WS_Destroy_Dialog(window, 0x5C2);
			}
			return(FALSE);

		case 0x686:
			WS_Destroy_Dialog(window, 0x686);
			return(FALSE);
		}
		return(FALSE);

	case 0x497:
		{
			HWND edit = GetDlgItem(window, 0x540);
			SendMessage(edit, EM_LIMITTEXT, 0x78, 0);
			SendMessage(edit, OD_SETLABEL, 0, (LPARAM)EmptyUIName);
			EnableWindow(GetDlgItem(window, 0x5C2), FALSE);
			HWND label = GetDlgItem(window, 0x712);
			SendMessage(label, OD_SETTEXT, 0, (LPARAM)g_SelectedBuddy.text());
		}
		return(FALSE);

	case WM_DRAWITEM:
		Dialog_On_WM_DRAWITEM(lparam);
		return(TRUE);

	case WM_PAINT:
		Dialog_On_WM_PAINT(window);
		Slide_Pending_Dialog(window);
		ValidateRect(window, NULL);
		return(TRUE);

	case WM_ERASEBKGND:
		return(TRUE);
	}
	return(FALSE);
}
