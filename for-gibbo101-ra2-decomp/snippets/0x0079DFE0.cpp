// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0079DFE0 (1335 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x346400 (VA 0x00746400, 1344 bytes incl. padding)
// RA2 symbol : ?WOL_Add_Buddy_Dialog_Proc@@YGHPAUHWND__@@IIJ@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9890)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

BOOL CALLBACK WOL_Add_Buddy_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) // RA2: 1.001 0x00746400, the dialog that adds a buddy by name: 0x540 is the name, 0x702 adds it
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
	case WM_COMMAND:
		switch (LOWORD(wparam)) {
		case 0x540:
			if (HIWORD(wparam) != 0) {
				Wstring name;
				Get_Control_Text((HWND)lparam, name);
				EnableWindow(GetDlgItem(window, 0x702), Is_Valid_New_Buddy(name));
			}
			return(FALSE);

		case 0x686:
			control->Set_Window((unsigned int)window, (HWND)0x686);
			return(FALSE);

		case 0x702:
			{
				Wstring name;
				HWND edit = GetDlgItem(window, 0x540);
				Get_Control_Text(edit, name);
				SendMessage(edit, OD_SETTEXT, 0, (LPARAM)NullString);
				if (Is_Valid_New_Buddy(name)) {
					Add_Buddy(name);
				}
				InvalidateRect(edit, NULL, FALSE);
				control->Set_Window((unsigned int)window, (HWND)0x702);
			}
			return(FALSE);
		}
		return(FALSE);

	case 0x497:
		{
			HWND edit = GetDlgItem(window, 0x540);
			SendMessage(edit, EM_LIMITTEXT, 9, 0);
			SendMessage(edit, 0x4D1, 1, 0);
			SendMessage(edit, OD_SETTEXT, 0, (LPARAM)NullString);
			EnableWindow(GetDlgItem(window, 0x702), FALSE);
		}
		return(FALSE);

	case 0x4DA:
		PostMessage(GetDlgItem(window, 0x702), BM_CLICK, 0, 0);
		return(FALSE);

	case WM_DRAWITEM:
		Dialog_On_WM_DRAWITEM(lparam);
		return(TRUE);

	case WM_PAINT:
		Dialog_On_WM_PAINT(window);
		Slide_Pending_Dialog(window);
		ValidateRect(window, NULL);
		// RA2: falls through
	case WM_ERASEBKGND:
		return(TRUE);
	}
	return(FALSE);
}
