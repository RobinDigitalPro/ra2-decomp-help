// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007A0430 (593 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x3486b0 (VA 0x007486B0, 608 bytes incl. padding)
// RA2 symbol : ?Queue_User_Pings@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9610)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Queue_User_Pings(void) // RA2: 1.001 0x007486B0, puts every user of the channel except operators and the player into the ping request list
{
	User user;
	memset(&user, 0, sizeof(user));
	DebugString("User list is %d long, adding to ping request queue\n", g_UserList.length());
	for (int i = 0; i < g_UserList.length(); i++) {
		g_UserList.get(user, i);
		if (user.flags & 1) {
			DebugString("%s is channel operator, no ping request\n", user.name);
		} else if (stricmp((char *)user.name, g_NickName.get()) == 0) {
			DebugString("%s is local user, no ping request\n", user.name);
		} else {
			Wstring name((char *)user.name);
			DebugString("Adding %s to ping request queue\n", name.get());
			g_PingRequests.addTail(name);
		}
	}
}
