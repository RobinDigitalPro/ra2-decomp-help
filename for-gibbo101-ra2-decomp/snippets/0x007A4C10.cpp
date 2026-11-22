// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007A4C10 (681 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x34c080 (VA 0x0074C080, 688 bytes incl. padding)
// RA2 symbol : ?OnUpdateList@CChatEventSink@@UAGJJPAUUpdate@@@Z
// similarity : 0.9689 (very-similar, masked instruction tokens; shape 0.9822)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

STDMETHODIMP CChatEventSink::OnUpdateList(HRESULT res, Update *updates)
{
	int count = 0;
	char working_dir[257];
	char fullpath[257];
	char localfile[257];
	wchar_t status[200];
	if (res < 0 || updates == NULL) {
		SetEvent(g_WaitEventHandles[EV_ABORT]);
		return(S_OK);
	}
	g_SuspendChatPump = 1;
	Update * tmp = updates;
	while (tmp != NULL) {
		tmp = tmp->next;
		count++;
	}
	Close_Wait_Window(0x10);
	if (ODMessageBox(StringTable::LoadString("TXT_UPGRADEREQUIRED", NULL, "C:\\RA2\\wonline.cpp", 3875), MB_YESNO, Wait_Callback_Thunk, false) == IDNO) {
		SetEvent(g_WaitEventHandles[EV_ABORT]);
		return(S_OK);
	}
	GetCurrentDirectoryA(0x100, working_dir);
	int i = 0;
	while (updates != NULL) {
		sprintf(fullpath, "%s/%s", updates->patchpath, updates->patchfile);
		sprintf(localfile, "%s\\%s", updates->localpath, updates->patchfile);
		CreateDirectoryA((char *)updates->localpath, NULL);
		g_pDownload->DownloadFile((char *)updates->server, (char *)updates->login, (char *)updates->password, fullpath, localfile, "SOFTWARE\\Westwood\\Red Alert 2");
		i++;
		swprintf(status, StringTable::LoadString("TXT_DOWNLOADING_X_OF_Y", NULL, "C:\\RA2\\wonline.cpp", 3897), i, count);
		WideWstring text(status);
		SimpleWonlineDialogControl control;
		HWND dialog = OwnerDraw::Begin_Dialog(0xD3, (DLGPROC)WOL_Download_Dialog_Proc, 0);
		HWND title = GetDlgItem(dialog, 0x5C7);
		SendMessageA(title, 0x4B2, 0, (LPARAM)text.text());
		if (WS_Wait_Dialog(dialog, Wait_Callback_Thunk, false, true, true) == IDCANCEL) {
			SetEvent(g_WaitEventHandles[EV_ABORT]);
			SetCurrentDirectoryA(working_dir);
			return(S_OK);
		}
		updates = updates->next;
	}
	ODMessageBox(StringTable::LoadString("TXT_GAME_RESTART", NULL, "C:\\RA2\\wonline.cpp", 3929), 0, Wait_Callback_Thunk, false);
	SetEvent(g_WaitEventHandles[EV_QUITGAME]);
	SetCurrentDirectoryA(working_dir);
	return(S_OK);
}
