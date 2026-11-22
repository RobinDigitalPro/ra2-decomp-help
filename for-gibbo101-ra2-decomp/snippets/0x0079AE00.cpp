// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0079AE00 (260 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x343390 (VA 0x00743390, 272 bytes incl. padding)
// RA2 symbol : ?Wonline_Autologin_Dialog_Proc@@YGJPAUHWND__@@IIJ@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9439)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

LRESULT CALLBACK Wonline_Autologin_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) // RA2: 0x00755070 (1.001 0x00743390), the dialog (0x112) after a login: OK keeps the nickname as the auto login persona, Cancel sets the auto login from the check box 0x6F9
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
		return(1);
	case WM_PAINT:
		Dialog_On_WM_PAINT(window);
		Slide_Pending_Dialog(window);
		ValidateRect(window, NULL);
		return(1);
	case WM_DRAWITEM:
		Dialog_On_WM_DRAWITEM(lparam);
		return(1);
	case WM_COMMAND:
		switch (LOWORD(wparam)) {
		case IDOK:
			WOL_Set_Auto_Login_Persona(g_NickName);
			control->Set_Window((unsigned int)window, (HWND)1);
			break;
		case IDCANCEL:
			{
				bool checked = IsDlgButtonChecked(window, 0x6F9) == BST_CHECKED;
				WOL_Set_Auto_Login(!checked);
				control->Set_Window((unsigned int)window, (HWND)2);
			}
			break;
		}
		break;
	}
	return(0);
}
