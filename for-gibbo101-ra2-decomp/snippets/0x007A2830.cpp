// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007A2830 (127 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x34a240 (VA 0x0074A240, 128 bytes incl. padding)
// RA2 symbol : ?WOL_Kick_User@@YIXABVWstring@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9907)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void WOL_Kick_User(Wstring const & name) // RA2: 1.001 0x0074A240, has the chat service kick the channel user of this name (no caller in 1.001)
{
	User user;
	user.flags = 0;
	for (int i = 0; i < g_UserList.length(); i++) {
		g_UserList.get(user, i);
		if (stricmp(name.text(), (char *)user.name) == 0) {
			g_pChat->RequestUserKick(&user);
			return;
		}
	}
}
