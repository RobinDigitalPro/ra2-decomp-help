// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0079CBA0 (707 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x344fe0 (VA 0x00744FE0, 720 bytes incl. padding)
// RA2 symbol : ?Remove_Buddy@@YIXABVWstring@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9713)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Remove_Buddy(Wstring const & name) // RA2: 1.001 0x00744FE0, removes the buddy from the list, forgets its channel and status and asks the chat service to delete it
{
	Channel channel;
	User user;
	for (int i = 0; i < g_BuddyList.length(); i++) {
		Wstring entry;
		g_BuddyList.get(entry, i);
		if (entry == name) {
			g_BuddyList.remove(i);
			Wstring key(name);
			Forget_Buddy_Channel(key, channel);
			g_BuddyStatus.remove(key);
			memset(&user, 0, sizeof(user));
			strncpy((char *)user.name, name.text(), 9);
			g_pChat->Unknown_Virtual_E4(&user); // RA2: the buddy delete request (YR: RequestBuddyDelete)
			return;
		}
	}
}
