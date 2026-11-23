// ra2-decomp help snippet, update 2 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00787770 (2568 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0x337c50 (VA 0x00737C50, 2191 bytes without padding)
// RA2 symbol : ?Run_Lobby_Session@@YIHH@Z
// similarity : 0.7545 (partial, masked instruction tokens; shape 0.8336)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/wonline.cpp
// License    : GPL-3.0-or-later. Our source is GPL and contains EA GPL code (section 7 terms)
//              and code adapted from mischa85/RedAlert2 and gibbo101/ra2-decomp; their
//              credits are kept. The notice of the source file follows. See ../README.md.
// Use        : a read-only lead. RA2 layouts and names; port it and match it on your own checker.

/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2025 Electronic Arts Inc.
 * Copyright 2026 OpenTS contributors
 *
 * Contains material derived from Electronic Arts source code.
 * Modified by OpenTS contributors, 2026.
 * EA's GPLv3 Section 7 additional terms and supplemental warranty
 * disclaimers apply; see LICENSE.md.
 ******************************************************************************/

int __fastcall Run_Lobby_Session(int dialog_arg) // level-2 1.001: 0x00737C50 (1.006 0x00743720), the chat lobby: plays the voice of the last World Domination Tour game, logs in again after a lost connection, opens the lobby dialog (0x113) with the message of the day, requests the channel list, joins a lobby and waits until the player leaves (0), quits (2) or a game starts (1); the argument is the HWND of a lobby dialog that is already open (Wonline_Main passes 0)
{
	int result = 0;
	HWND & dialog = (HWND &)dialog_arg; // level-2 1.001: the argument itself holds the dialog (ebp), it is replaced by the new dialog

	if (g_PlayingNetGame && Session.Type == GAME_INTERNET && Online_Session_State == 2 && ScoreData.WinnerIndex != -1 && ScoreData.WinnerIndex < 8) { // level-2 1.001: the voice of the tour after a game
		Wstring winner = Wstring_Narrow(ScoreData.Records[ScoreData.WinnerIndex].Name);
		if (strnicmp(winner.get(), Session.Handle, 20) == 0) { // level-2 1.001: the player won
			if (Session.House == 0) {
				Play_WDT_Sound(g_WDT_GDIWinEmphasisSounds);
			} else if (Session.House == 1) {
				Play_WDT_Sound(g_WDT_NodWinEmphasisSounds);
			}
		} else if (Session.House == 0) {
			Play_WDT_Sound(g_WDT_GDILoseEmphasisSounds);
		}
	}
	g_PlayingNetGame = false;
	WolOptionsLocked = 0;
	if (Session.Type == GAME_INTERNET && Online_Session_State == 2) {
		g_pChat->RequestSetTeam(Session.House);
		if (!g_WDTSoundsInited) {
			Init_WDT_Sounds();
		}
	}

	if (g_ConnectionLost) {
		int login = Login_Wonline();
		if (login != 1) {
			return(login);
		}
	}
	Reset_All_Wait_Events(); // level-2 1.001 (a12): the file's helper, not a flat loop (inline call sites: VC6 then calls ArrayList<Wstring>::get 0x00752730 out of line in the three Play_WDT_Sound copies)

	if (dialog == NULL) {
		Darken_Surface(NULL, true);
		dialog = OwnerDraw::Begin_Dialog(0x113, (DLGPROC)Wonline_Chat_Lobby_Dialog_Proc, 0);
		if (g_Motd.length() > 0) { // level-2 1.001: the message of the day, line by line
			char * motd = new char[g_Motd.length() + 1];
			if (motd) {
				strcpy(motd, g_Motd.get());
				char * line = strtok(motd, "\n");
				while (line) {
					WideWstring text = Widen_Text(line); // level-2 1.001 (a12): the file's helper, as in the chat handlers
					Lobby_Chat_Printf(ColorSystem, text.get());
					line = strtok(NULL, "\n");
				}
				Lobby_Chat_Printf(ColorSystem, L"\n");
				g_Motd.clear();
				delete [] motd;
			}
		}
		Show_Wait_Window(0x10, StringTable::LoadString("GUI:LoginComplete", NULL, "C:\\RA2\\wonline.cpp", 7879), false);
	}

	g_SquadInfoRequests++;
	g_RequestingOwnSquadInfo = 1;
	g_pChat->RequestSquadInfo(0);
	g_ServerType = 0x21;
	Set_Wait_Window_Text((LPARAM)StringTable::LoadString("TXT_REQ_CHANLIST", NULL, "C:\\RA2\\wonline.cpp", 7896));
	if (!Get_Channel_List(0, false)) goto done;
	Set_Wait_Window_Text((LPARAM)StringTable::LoadString("TXT_JOINLOB", NULL, "C:\\RA2\\wonline.cpp", 7946));
	if (Join_Selected_Lobby(true) == -1) goto done;
	{
		DWORD event;
		while ((event = WaitForMultipleObjects(EV_COUNT, g_WaitEventHandles, FALSE, 100)) == WAIT_TIMEOUT) {
			WOL_Wait_Callback();
		}
		Reset_Wait_Event_At(event); // level-2 1.001 (a12): as above
		if (event == EV_ABORT || event == EV_ERROR) goto leave;
	}
	g_JoinLobbyNow = 0;
	Close_Wait_Window(0xFFFFFFFF);
	SetFocus(MainWindow);
	ShowWindow(dialog, SW_SHOWNORMAL);
	SetFocus(dialog);
	SetFocus(GetDlgItem(dialog, 0x540));
	g_LastGameListTime = 0;
	g_LastChatListTime = time(0);
	for (;;) {
		DWORD event;
		while ((event = WaitForMultipleObjects(EV_COUNT, g_WaitEventHandles, FALSE, 20)) == WAIT_TIMEOUT) {
			WOL_Wait_Callback();
			if (g_JoinLobbyNow) { // level-2 1.001: the lobby is changed: its controls are off while the join runs
				EnableWindow(GetDlgItem(dialog, 0x53D), FALSE);
				EnableWindow(GetDlgItem(dialog, 0x6EE), FALSE);
				EnableWindow(GetDlgItem(dialog, 0x62D), FALSE);
				EnableWindow(GetDlgItem(dialog, 0x62B), FALSE);
				EnableWindow(GetDlgItem(dialog, 0x689), FALSE);
				EnableWindow(GetDlgItem(dialog, 0x558), FALSE);
				EnableWindow(GetDlgItem(dialog, 0x61F), FALSE);
				EnableWindow(GetDlgItem(dialog, 0x686), FALSE);
				if (Join_Selected_Lobby(false) == -1) {
					EnableWindow(GetDlgItem(dialog, 0x686), TRUE);
					SetEvent(g_WaitEventHandles[EV_ERROR]);
				}
				g_JoinLobbyNow = 0;
			}
		}
		Reset_Wait_Event_At(event); // level-2 1.001 (a12): as above
		if (event == EV_ABORT) {
			goto done;
		}
		if (event != EV_EXIT) { // level-2 1.001 (b5): the event tests in the 1.006 form (break in the else, the start of the game at the end); with the flat tests VC6 starts the zero web (ebx) after the first EV_ABORT test and the leave block's g_pChat test
			if (event == EV_SKIRMISH) {
				result = 2;
				break;
			}
			if (event == EV_ERROR) {
				goto done;
			}
			if (event == EV_STARTGAME) {
				goto started;
			}
		} else {
			break;
		}
	}
	g_LastErrorMessage[0] = 0;
leave:
	WS_Destroy_Dialog(dialog, 0);
	WOL_Wait_Callback();
	dialog = NULL;
	if (g_pChat) {
		g_pChat->RequestChannelLeave();
	}
done:
	Close_Wait_Window(0xFFFFFFFF);
	ODMessageBox(g_LastErrorMessage, 0, Wait_Callback_Thunk, false);
	if (dialog) WS_Destroy_Dialog(dialog, 0);
	while (WS_Destroy_Dialog(NULL, 0)) {
	}
	if (result == 1) {
		g_PlayingNetGame = true;
	}
	if (Session.Type == GAME_INTERNET && Online_Session_State == 2) {
		g_WDTTeams.clear();
	}
	return(result);
started:
	result = 1;
	g_pChat->RequestChannelLeave();
	g_GameStartRequested = false;
	g_LastErrorMessage[0] = 0;
	goto done;
}
