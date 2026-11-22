// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007ABFA0 (633 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x351960 (VA 0x00751960, 640 bytes incl. padding)
// RA2 symbol : ?OnSetTeam@CChatEventSink@@UAGJJH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9825)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

STDMETHODIMP CChatEventSink::OnSetTeam(HRESULT res, int newteam) // level-2 1.001: 0x00751960, the server confirmed the persona's new team: the session house and the team dictionary entry are replaced
{
	if (res == 0) {
		Session.House = newteam;
		Wstring name;
		char handle[64];
		strcpy(handle, Session.Handle);
		name.set(handle);
		name.toLower();
		if (g_WDTTeams.contains(name)) {
			g_WDTTeams.remove(name);
		}
		g_WDTTeams.add(name, newteam);
		return(S_OK);
	}
	DebugString("OnSetTeam FAILED: %d\n", newteam);
	return(S_OK);
}
