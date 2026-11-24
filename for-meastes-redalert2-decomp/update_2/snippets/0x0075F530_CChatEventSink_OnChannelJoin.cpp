// RA2 1.001 byte-identical (VC6 8168 /O2 /Ob2 /Gr /GR /Gy), RVA 0x34cb20, from our src/m85/src/wonline.cpp. GPL-3.0-or-later.
// Your 1.006 entry 0x0075F530 (CChatEventSink::OnChannelJoin, 5780 bytes, non_exact in your map).

STDMETHODIMP CChatEventSink::OnChannelJoin(HRESULT res, Channel *channel, User *user) // level-2 1.001: 0x0074CB20, a user (or the persona itself) joined a channel: a failed join is reported and the pending channel forgotten; the persona's own join of a lobby enables the lobby dialog, of a game channel sets up the session and opens the guest dialog (0xC9); another user is queued for its team, locale and ladder, added to the sorted user list and to the slots (by the host); body after gibbo101 YR CChatEventSink::OnChannelJoin, without YR's observers, highscores and mangler code
{
	if (res == 0x8004006C) {
		return(S_OK);
	}
	int i;
	int players;
	wchar_t joinname[64];
	joinname[0] = 0;
	if (channel) {
		Char_To_Wide(joinname, (char *)channel->name, -1);
		if (strncmp((char *)channel->name, "Lob_33_", 7) == 0) {
			int lobby = atol((char *)channel->name + strlen("Lob_33_"));
			int d = lobby / 6; // level-2 1.001: six lobby names
			int m = lobby % 6;
			if (d == 0) {
				swprintf(joinname, L"%s", g_Lobbies[m]);
			} else {
				swprintf(joinname, L"%s %d", g_Lobbies[m], d + 1);
			}
		}
	}
	if (res < 0) {
		if (res == 0x80040070) {
			Channel *chan = NULL;
			for (int channelIndex = 0; channelIndex < g_UserChannels.length(); channelIndex++) {
				g_UserChannels.getPointer(&chan, channelIndex);
				if (strcmp((char *)g_PendingChannel.name, (char *)chan->name) == 0) {
					g_UserChannels.remove(channelIndex);
					break;
				}
			}
			for (int gameIndex = 0; gameIndex < g_GameChannelList.length(); gameIndex++) {
				g_GameChannelList.getPointer(&chan, gameIndex);
				if (strcmp((char *)g_PendingChannel.name, (char *)chan->name) == 0) {
					g_GameChannelList.remove(gameIndex);
					break;
				}
			}
			if (Is_Tournament_Session()) {
				Lobby_Chat_Printf(ColorSystem, StringTable::LoadString("TXT_GAME_CLOSED", NULL, "C:\\RA2\\wonline.cpp", 4290)); // level-2 1.001: line literal
				SetEvent(g_WaitEventHandles[EV_ERROR]);
			} else {
				ODMessageBox(StringTable::LoadString("TXT_GAME_CLOSED", NULL, "C:\\RA2\\wonline.cpp", 4293), 0, Wait_Callback_Thunk, false); // level-2 1.001: line literal
			}
		} else if (res == 0x80040071) {
			if (Is_Tournament_Session()) {
				Lobby_Chat_Printf(ColorSystem, StringTable::LoadString("TXT_BADPASS", NULL, "C:\\RA2\\wonline.cpp", 4300)); // level-2 1.001: line literal
				SetEvent(g_WaitEventHandles[EV_ERROR]);
			} else {
				ODMessageBox(StringTable::LoadString("TXT_BADPASS", NULL, "C:\\RA2\\wonline.cpp", 4303), 0, Wait_Callback_Thunk, false); // level-2 1.001: line literal
			}
		} else if (res == 0x8004006E) {
			if (Is_Tournament_Session()) {
				Lobby_Chat_Printf(ColorSystem, StringTable::LoadString("TXT_CHANNEL_FULL", NULL, "C:\\RA2\\wonline.cpp", 4310)); // level-2 1.001: line literal
				SetEvent(g_WaitEventHandles[EV_ERROR]);
			} else {
				ODMessageBox(StringTable::LoadString("TXT_CHANNEL_FULL", NULL, "C:\\RA2\\wonline.cpp", 4313), 0, Wait_Callback_Thunk, false); // level-2 1.001: line literal
				if (g_PendingChannel.type == 0) {
					SetEvent(g_WaitEventHandles[EV_ERROR]);
				}
			}
		} else if (res == 0x80040072) {
			ODMessageBox(StringTable::LoadString("TXT_JOINBAN", NULL, "C:\\RA2\\wonline.cpp", 4322), 0, Wait_Callback_Thunk, false); // level-2 1.001: line literal
			SetEvent(g_WaitEventHandles[EV_ERROR]);
			g_LobbyNumber++;
		} else {
			Lobby_Chat_Printf(ColorSystem, StringTable::LoadString("TXT_CANT_JOINCHAN", NULL, "C:\\RA2\\wonline.cpp", 4329), res); // level-2 1.001: line literal
			SetEvent(g_WaitEventHandles[EV_ERROR]);
		}
		g_IsChannelCreator = 0;
		g_CurrentChannel.name[0] = 0;
		memset(&g_PendingChannel, 0, sizeof(Channel));
		Close_Wait_Window(2);
		g_PendingChannel.name[0] = 0;
		Refresh_Game_List();
		Draw_Player_List(0, false);
		SetEvent(g_WaitEventHandles[EV_CHAN_JOIN_FAIL]);
		g_JoinLobbyNow = (g_PendingChannel.type != 0);
		HWND main = WS_Find_Dialog(0x113);
		if (main) {
			ShowWindow(main, SW_SHOW);
			OwnerDraw::Set_Paint_Disabled(main, 0);
		}
		return(S_OK);
	}

	g_PendingChannel.name[0] = 0;
	if (user->flags & 0x8000) {
		memcpy(&g_CurrentChannel, channel, sizeof(Channel));
		memset(&g_PendingChannel, 0, sizeof(Channel));
		Close_Wait_Window(2);
		g_ChannelCount++;
		DebugString("Joined Channel\n");
		g_LobbyNumber = atol((char *)channel->name + strlen("Lob_33_"));
		if (!Is_Tournament_Session()) {
			Lobby_Chat_Printf(ColorSystem, StringTable::LoadString("TXT_JOINED_S", NULL, "C:\\RA2\\wonline.cpp", 4377), joinname); // level-2 1.001: line literal
		}
		if (channel->type == 0) {
			HWND main = WS_Find_Dialog(0x113);
			if (main) {
				EnableWindow(GetDlgItem(main, 0x53D), TRUE);
				bool join = false;
				HWND list = GetDlgItem(main, 0x6EE);
				int index = SendMessage(list, LB_GETCURSEL, 0, 0);
				if (index != LB_ERR) {
					index = SendMessage(list, LB_GETITEMDATA, index, 0);
					if (index >= 0 && index < g_GameChannelList.length()) {
						Channel choice;
						memset(&choice, 0, sizeof(choice));
						g_GameChannelList.get(choice, index);
						join = Can_Join_Channel(&choice, false);
					}
				}
				EnableWindow(GetDlgItem(main, 0x6EE), TRUE);
				EnableWindow(GetDlgItem(main, 0x62D), join);
				EnableWindow(GetDlgItem(main, 0x62B), TRUE);
				EnableWindow(GetDlgItem(main, 0x689), TRUE);
				EnableWindow(GetDlgItem(main, 0x558), TRUE);
				EnableWindow(GetDlgItem(main, 0x61F), TRUE);
				EnableWindow(GetDlgItem(main, 0x686), TRUE);
				SetFocus(GetDlgItem(main, 0x540));
			}
			Request_Channel_List(0x21, 1); // level-2 1.001: the game channel list is asked for without a wait (the request and its queue entry are expanded)
			Refresh_Lobby_List();
		}
		if (channel->type == 0x21) {
			Session.MPGameMode = Default_Game_Mode();
			Session.ScenarioMaxPlayers = 8;
			if (Session.MPGameMode) {
				Session.MPGameMode->vt_entry_24();
			}
			Delete_All(Session.Players);
			Clear_Slot_Lists();
			Reset_Slots();
			NodeNameType *node = new NodeNameType;
			memset(node, 0, sizeof(NodeNameType));
			wcscpy(node->Name, Narrow_To_Wide((char *)user->name));
			node->Address = User_To_IPX_Address(user);
			node->Set_Country(-2);
			node->Set_Color(-2);
			Session.Players.Add(node);
			Session.GameName[0] = 0;
			if (!Is_Tournament_Session()) {
				Darken_Surface(NULL, true);
				HWND dlg = WS_Create_Dialog(ProgramInstance, 0xC9, MainWindow, WOL_Guest_Dialog_Proc, 0);
				Show_Dialog(dlg, 0xC9);
				HWND main = WS_Find_Dialog(0x113);
				if (main) {
					ShowWindow(main, SW_HIDE);
					OwnerDraw::Set_Paint_Disabled(main, 0);
				}
				SendMessage(dlg, 0x4A9, 0, 1);
				ShowWindow(dlg, SW_SHOWNORMAL);
			}
		}
	} else {
		if (g_CurrentChannel.type == 0x21) {
			VocClass::PlayGlobal(Rule->PlayerJoined, 1.0f, 0x2000, 0);
		}
		if (user->squadID != 0 && strlen((char *)user->squadabbrev) == 0) {
			g_SquadInfoRequests++;
			g_pChat->RequestSquadInfo(user->squadID);
		}
		{
			Wstring ladder_name;
			ladder_name.set((char *)user->name);
			ladder_name.toLower();
			if (Session.Type == GAME_INTERNET && Online_Session_State == 2) {
				Wstring name;
				bool found = false;
				for (int teamIndex = 0; teamIndex < g_WDTTeamLookupQueue.length(); teamIndex++) {
					g_WDTTeamLookupQueue.get(name, teamIndex);
					if (name == ladder_name) {
						found = true;
						break;
					}
				}
				if (!found) {
					g_WDTTeamLookupQueue.addHead(ladder_name);
				}
			}
			if (!g_UserLocales.contains(ladder_name)) {
				Wstring name;
				bool found = false;
				for (int localeIndex = 0; localeIndex < g_UserLocaleLookupQueue.length(); localeIndex++) {
					g_UserLocaleLookupQueue.get(name, localeIndex);
					if (name == ladder_name) {
						found = true;
						break;
					}
				}
				if (!found) {
					g_UserLocaleLookupQueue.addHead(ladder_name);
				}
			}
			if (!g_ActiveLadder->contains(ladder_name)) {
				g_pNetUtil->RequestLadderList(g_LadderAddress, g_LadderPort, ladder_name.get(), g_GameSKU & 0xFFFF00, -1, 0, 0);
			}
		}
		if (channel->type != 0) {
			for (i = 1; i < 16; i++) {
				g_UserInfo[i].accepted = 0;
				EnableWindow(GetDlgItem(GameoptWindow(), 0x59F), TRUE);
			}
			if (!g_IsChannelCreator) {
				HWND dialog = WS_Find_Dialog(0xC9);
				Enable_Player_Combos(dialog, true);
			}
			Enable_Start_Button();
		}
	}

	int index = g_UserList.length();
	User temp_user;
	for (i = 0; i < g_UserList.length(); i++) {
		g_UserList.get(temp_user, i);
		if (Compare_Users(user, &temp_user) < 0) {
			index = i;
			break;
		}
	}
	User newuser = *user; // level-2 1.001: copied after the sorted position is found (no lobby special case as in YR)
	newuser.next = NULL;
	g_UserList.add(newuser, index);
	if (!(user->flags & 0x8000) && channel->type == 0 && (Online_Session_State == 2 || Online_Session_State == 1) && g_MatchState == 4) { // level-2 1.001: the tournament test is written out here and below (not Is_Tournament_Session): with the helper the ping addTail is called out of line
		Wstring name((char *)user->name);
		g_PingRequests.addTail(name);
		if (g_PingServers.length() == 0) {
			Request_Match_Pings();
		}
	}
	players = g_UserList.length();
	if (channel->type != 0) {
		char * name = (char *)user->name;
		int userinfoindex = Player_Name_To_Index(User_Name(user)); // level-2 1.001: through User_Name (by value), as in OnPrivateGameOptions; a plain Wstring temporary gives a frame 4 bytes larger
		memmove(&g_UserInfo[userinfoindex + 1], &g_UserInfo[userinfoindex], sizeof(ChannelUserInfo) * (15 - userinfoindex));
		memset(&g_UserInfo[userinfoindex], 0, sizeof(ChannelUserInfo));
		strcpy(g_UserInfo[userinfoindex].name, name);
		if (g_IsChannelCreator == 1) {
			if (Is_Game_Full()) {
				WOL_Kick_User(User_Name(user)); // level-2 1.001: a full game: the new user is kicked (WOL_Kick_User 0x0074A240 expanded)
			} else {
				int color = 0;
				int taken = 0;
				while (true) {
					g_UserInfo[userinfoindex].color = color;
					taken = 0;
					for (i = 0; i < players; i++) {
						if (i != userinfoindex && g_UserInfo[i].color == color) {
							color++;
							taken = 1;
						}
					}
					if (taken == 0) {
						break;
					}
				}
				NodeNameType *node = new NodeNameType;
				memset(node, 0, sizeof(NodeNameType));
				wcscpy(node->Name, Narrow_To_Wide(name));
				node->Address = User_To_IPX_Address(user);
				if (Session.MPGameMode) {
					node->Set_Country(Session.MPGameMode->DefaultCountry());
				} else {
					node->Set_Country(-2);
				}
				node->Set_Color(-2);
				Session.Players.Add(node);
				Add_To_Open_Slot((MPPlayerNode *)node);
				if ((Online_Session_State == 2 || Online_Session_State == 1) && channel->type != 0) {
					if (Online_Session_State != 2) {
						Net2DecodeGameopt(g_MatchStartOptions, NULL);
					} else {
						Setup_Match_Map(strchr(g_MatchStartOptions, ':'));
					}
					for (i = 0; i < Session.Scenarios.Count(); i++) {
						char const *filename = Session.Scenarios[i]->Get_Filename(); // level-2 1.001: a named local (as gibbo101 YR); the direct call gives other registers here and in the last branch
						if (stricmp(Session.ScenarioFileName, filename) == 0) {
							Set_Scenario_Info_From_Index(i);
							break;
						}
					}
					if (i >= Session.Scenarios.Count()) {
						Set_Scenario_Info_From_Index(0);
					}
				}
				Enable_Start_Button();
				Handle_Mode_Selection();
				Send_Player_List();
				Send_Lobby_Options(true, false);
			}
		} else if (!(user->flags & 0x8000)) {
			NodeNameType *node = new NodeNameType;
			memset(node, 0, sizeof(NodeNameType));
			wcscpy(node->Name, Narrow_To_Wide(name));
			node->Address = User_To_IPX_Address(user);
			node->Set_Country(-2);
			node->Set_Color(-2);
			Session.Players.Add(node);
			HWND dialog = WS_Find_Dialog(0xC9);
			Enable_Player_Combos(dialog, true);
			Enable_Start_Button();
		}
	}
	SetEvent(g_WaitEventHandles[EV_CHAN_JOINED]);
	Draw_Player_List(0, false);
	return(S_OK);
}
