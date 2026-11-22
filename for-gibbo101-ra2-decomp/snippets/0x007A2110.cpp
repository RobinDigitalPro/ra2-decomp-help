// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007A2110 (287 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x349cb0 (VA 0x00749CB0, 288 bytes incl. padding)
// RA2 symbol : ?WOL_Match_Wait_Dialog_Proc@@YGHPAUHWND__@@IIJ@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9944)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

BOOL CALLBACK WOL_Match_Wait_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) // RA2: 1.001 0x00749CB0, the dialog (0x117) while the quick match is searched; 0x708/0x709 are test buttons
{
	switch (message) {
	case WM_DESTROY:
		KillTimer(window, 0);
		return(FALSE);

	case WM_PAINT:
		Dialog_On_WM_PAINT(window);
		Slide_Pending_Dialog(window);
		ValidateRect(window, NULL);
		return(TRUE);

	case WM_ERASEBKGND:
		return(TRUE);

	case WM_DRAWITEM:
		Dialog_On_WM_DRAWITEM(lparam);
		return(TRUE);

	case WM_COMMAND:
		switch (LOWORD(wparam)) {
		case 0x5C0:
			if (g_MatchState == 11) {
				WS_Destroy_Dialog(window, 0);
				return(FALSE);
			}
			SetEvent(g_WaitEventHandles[0]);
			break;

		case 0x708:
			g_pChat->RequestPublicMessage("start 4439,0,0,10000,10,1,1,1,3,Match,1,0,MP18S3.MAP,Match:mshag,4,1,xyzkerble,7,4");
			return(FALSE);

		case 0x709:
			g_pChat->RequestPublicMessage("start 4439,0,0,10000,10,1,1,1,3,Match,1,0,MP18S3.MAP,Match:xyzkerble,7,4,mshag,4,1,");
			return(FALSE);
		}
		break;

	case WM_TIMER:
		if (wparam == 0) {
			Add_Chat_Dot();
			return(FALSE);
		}
		break;

	case 0x497:
		SetTimer(window, 0, 2000, NULL);
		return(FALSE);
	}
	return(FALSE);
}
