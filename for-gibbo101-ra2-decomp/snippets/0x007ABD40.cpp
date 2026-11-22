// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007ABD40 (607 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x351700 (VA 0x00751700, 608 bytes incl. padding)
// RA2 symbol : ?OnUserTeam@CChatEventSink@@UAGJJPAUUser@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9973)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

STDMETHODIMP CChatEventSink::OnUserTeam(HRESULT res, User *users) // level-2 1.001: 0x00751700, the tournament teams of users go into the team dictionary, then the player list is redrawn
{
	if (res >= 0) {
		User * user = users;
		Wstring name;
		while (user != NULL) {
			name.set((char *)user->name);
			if (g_WDTTeams.contains(name)) {
				g_WDTTeams.remove(name);
			}
			int team = user->team;
			g_WDTTeams.add(name, team);
			user = user->next;
		}
		Draw_Player_List(0, false);
		return(S_OK);
	}
	DebugString("OnUserTeam FAILED!\n");
	return(S_OK);
}
