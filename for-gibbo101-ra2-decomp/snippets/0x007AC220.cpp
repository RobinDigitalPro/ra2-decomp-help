// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007AC220 (637 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x351be0 (VA 0x00751BE0, 656 bytes incl. padding)
// RA2 symbol : ?OnBuddyList@CChatEventSink@@UAGJJPAUUser@@@Z
// similarity : 0.9700 (very-similar, masked instruction tokens; shape 0.9784)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

STDMETHODIMP CChatEventSink::OnBuddyList(HRESULT res, User *buddyList) // level-2 1.001: 0x00751BE0, slot 35 of IChatEvent: the buddies of the persona from the server go into the buddy lists, then the ladders of the buddies are asked for and the buddy dialog (0x116) is refilled
{
	if (res >= 0) {
		for (User * user = buddyList; user != NULL; user = user->next) {
			Wstring name((char *)user->name);
			Add_Buddy_Name(name);
		}
		Request_Buddy_Ladders();
		Close_Wait_Window(0x200);
		HWND list = WS_Find_Dialog(0x116);
		if (list != NULL) {
			Fill_Buddy_List(list);
			SendMessageA(list, 0x4A9, 0, 1);
			KillTimer(list, 0x704);
			EnableWindow(GetDlgItem(list, 0x704), TRUE);
		}
	}
	return(S_OK);
}
