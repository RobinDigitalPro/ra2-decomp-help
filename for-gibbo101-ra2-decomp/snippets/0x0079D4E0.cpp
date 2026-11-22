// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0079D4E0 (565 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x345920 (VA 0x00745920, 544 bytes incl. padding)
// RA2 symbol : ?Reset_Buddy_Lists@@YIXXZ
// similarity : 0.9711 (very-similar, masked instruction tokens; shape 0.9441)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Reset_Buddy_Lists(void) // RA2: 1.001 0x00745920, clears the buddy lists, asks for the buddy list and refreshes their channels and ladder entries
{
	g_BuddyList.clear();
	g_BuddyRequests.clear();
	g_BuddyStatus.clear();
	g_BuddyChannels.clear();
	g_pChat->Unknown_Virtual_DC(); // RA2: the buddy list request (YR: RequestBuddyList)
	Refresh_Buddy_Channels();
	Request_All_Buddy_Ladders();
}
