// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007A2600 (303 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x34a020 (VA 0x0074A020, 304 bytes incl. padding)
// RA2 symbol : ?WOL_Match_Found_Dialog_Proc@@YGHPAUHWND__@@IIJ@Z
// similarity : 0.9902 (very-similar, masked instruction tokens; shape 0.9951)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

BOOL CALLBACK WOL_Match_Found_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) // RA2: 1.001 0x0074A020, the dialog (0x11F) of the found quick match with the map preview
{
	int result = Standard_Dialog_Proc(window, message, wparam, lparam);
	if (result) {
		return(result);
	}
	switch (message) {
	case WM_COMMAND:
		if (LOWORD(wparam) == 0x5C0) {
			SetEvent(g_WaitEventHandles[0]);
			WS_Destroy_Dialog(window, 0x5C0);
		}
		break;

	case WM_DESTROY:
		if (MultiplayerMapPreview) {
			delete MultiplayerMapPreview;
			MultiplayerMapPreview = NULL;
		}
		return(FALSE);

	case WM_PAINT:
		Dialog_On_WM_PAINT(window);
		Slide_Pending_Dialog(window);
		if (MultiplayerMapPreview) {
			MultiplayerMapPreview->Blit_Preview(window);
		} else if (Session.Options.ScenarioIndex == -1 && RandomMapGen.MapPreview) {
			RandomMapGen.MapPreview->Blit_Preview(window);
		}
		if (Progress.Has_Dialog()) {
			Progress.Display_Progress();
		}
		ValidateRect(window, NULL);
		return(TRUE);

	case WM_ERASEBKGND:
		return(TRUE);

	case WM_DRAWITEM:
		Dialog_On_WM_DRAWITEM(lparam);
		return(TRUE);

	case 0x5C0:
		return(FALSE);
	}
	return(FALSE);
}
