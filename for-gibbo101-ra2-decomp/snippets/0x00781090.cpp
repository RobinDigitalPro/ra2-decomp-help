// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00781090 (153 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x333fa0 (VA 0x00733FA0, 160 bytes incl. padding)
// RA2 symbol : ?User_List_Tooltip@@YI?AVWideWstring@@PAUHWND__@@H@Z
// similarity : 0.9615 (very-similar, masked instruction tokens; shape 0.9369)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

WideWstring User_List_Tooltip(HWND list, int row) // RA2: 0x0073F850, the tooltip of a row of the user list: User_Tooltip of the user
{
	if (row == -1) { // RA2: as above
		return(WideWstring(StringTable::LoadString("STT:LobbyListUsers", NULL, "C:\\RA2\\wonline.cpp", 2449))); // RA2: as above // level-2 1.001: line literal
	}
	int index = SendMessageA(list, LB_GETITEMDATA, row, 0);
	if (index >= 0 && index < g_UserList.length()) { // RA2: as above
		User user;
		memset(&user, 0, sizeof(user));
		g_UserList.get(user, index);
		return(User_Tooltip(user));
	}
	return(WideWstring(StringTable::LoadString("STT:LobbyListUsers", NULL, "C:\\RA2\\wonline.cpp", 2454))); // RA2: as above // level-2 1.001: line literal
}
