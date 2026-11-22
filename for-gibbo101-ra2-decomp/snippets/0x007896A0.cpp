// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007896A0 (702 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x339910 (VA 0x00739910, 704 bytes incl. padding)
// RA2 symbol : ?Populate_Server_Choices@@YI_NPAUHWND__@@_N@Z
// similarity : 0.9907 (very-similar, masked instruction tokens; shape 0.9954)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool Populate_Server_Choices(HWND list, bool combo) // RA2: 0x007454C0, not in TibSun: fills a list box (or combo box) with the names of the chat servers and selects the one of the persona's profile; false when the server list is empty
{
	if (combo) { // RA2: as above
		Clear_ComboBox(list); // RA2: as above
	} else {
		Clear_Listbox(list); // RA2: as above
	}
	if (g_Servers.length() == 1) { // RA2: only the entry 0 of the list: no server to choose from
		if (combo) { // RA2: as above
			SendMessage(list, OD_ADDSTRING_COMBO, 0, (LPARAM)"GUI:NoServersAvailable"); // RA2: as above
		} else {
			SendMessage(list, OD_ADDSTRING_LIST, 0, (LPARAM)"GUI:NoServersAvailable"); // RA2: as above
		}
		EnableWindow(list, FALSE); // RA2: as above
		return(false); // RA2: as above
	}
	Wstring preferred; // RA2: the server of the persona's profile
	WOLOptionsClass options; // RA2: as in Connect_To_Server
	options.Load(); // RA2: as above
	rc_ptr<PlayerProfile> profile; // RA2: as above
	if (options.Is_Bit1_Clear()) { // RA2: as above
		profile = PlayerProfile::Load(g_NickName); // RA2: as above
	} else {
		profile = g_PlayerProfile.Get(); // RA2: as above
	}
	if (profile.Get()) { // RA2: as above
		preferred = profile->Name; // RA2: as above
	}
	EnableWindow(list, TRUE); // RA2: as above
	int selected = -1; // RA2: as above
	for (int i = 1; i < g_Servers.length(); i++) { // RA2: as above
		Server * server = NULL; // RA2: as above
		g_Servers.getPointer(&server, i); // RA2: as above
		DebugString("Server found %s\n", (char *)server->name); // RA2: as above
		Wstring display = Server_Name_Without_Prefix(server); // RA2: expanded here
		int row; // RA2: as above
		if (combo) { // RA2: as above
			row = SendMessage(list, OD_ADDSTRING_COMBO, 0, (LPARAM)display.text()); // RA2: as above
			SendMessage(list, CB_SETITEMDATA, row, i); // RA2: as above
		} else {
			row = SendMessage(list, OD_ADDSTRING_LIST, 0, (LPARAM)display.text()); // RA2: as above
			SendMessage(list, LB_SETITEMDATA, row, i); // RA2: as above
		}
		if (preferred.length() > 0) { // RA2: as above
			bool match = ((Wstring const &)preferred).toLower() == ((Wstring const &)display).toLower(); // RA2: the const toLower returns a copy
			if (match) { // RA2: as above
				selected = row; // RA2: as above
				g_CurrentServerIndex = i; // RA2: the server of the profile becomes the one to connect to
				g_TargetServerIndex = i; // RA2: as above
			}
		}
	}
	if (selected == -1) { // RA2: as above
		selected = 0; // RA2: as above
	}
	if (combo) { // RA2: as above
		SendMessage(list, CB_SETCURSEL, selected, 0); // RA2: as above
	} else {
		SendMessage(list, LB_SETCURSEL, selected, 0); // RA2: as above
		SendMessage(list, LB_SETTOPINDEX, selected, 0); // RA2: as above
	}
	return(true); // RA2: as above
}
