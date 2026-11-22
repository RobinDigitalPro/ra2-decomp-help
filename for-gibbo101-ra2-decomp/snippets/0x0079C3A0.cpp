// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0079C3A0 (380 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x3447e0 (VA 0x007447E0, 384 bytes incl. padding)
// RA2 symbol : ?Request_Next_Buddy_Find@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9837)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Request_Next_Buddy_Find(void) // RA2: 1.001 0x007447E0, asks the chat service for the channel of the next buddy of the request list (one every 5 seconds)
{
	if (g_BuddyFindName.length() > 0) {
		if ((unsigned)(time(NULL) - g_BuddyFindTime) < 5) {
			return;
		}
		g_BuddyFindName.clear();
	}
	if (g_BuddyRequests.length() == 0) {
		return;
	}
	g_BuddyRequests.removeHead(g_BuddyFindName);
	g_BuddyFindTime = time(NULL);
	User user;
	memset(&user, 0, sizeof(user));
	strcpy((char *)user.name, g_BuddyFindName.get());
	g_pChat->RequestFind(&user);
}
