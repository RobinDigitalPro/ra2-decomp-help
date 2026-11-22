// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007AB8E0 (527 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x3512a0 (VA 0x007512A0, 528 bytes incl. padding)
// RA2 symbol : ?OnUserLocale@CChatEventSink@@UAGJJPAUUser@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9968)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

STDMETHODIMP CChatEventSink::OnUserLocale(HRESULT res, User *users) // level-2 1.001: 0x007512A0, the locales of users from the server go into the locale dictionary; the persona's own locale is also stored in its profile and ends the locale wait
{
	bool found = false;
	if (res < 0) {
		DebugString("OnUserLocale callback failed!\n");
		return(S_OK);
	}
	User * user = users;
	while (user != NULL) {
		Wstring name;
		name.set((char *)user->name);
		name.toLower();
		g_UserLocales.remove(name); // level-2 1.001: the one-argument remove (its inner remove(key, value) 0x00753680 stays out of line, add is expanded)
		int locale = user->locale;
		g_UserLocales.add(name, locale);
		if (stricmp((char *)users->name, g_NickName.get()) == 0) {
			WOLOptionsClass options;
			options.Load();
			rc_ptr<PlayerProfile> profile;
			if (options.Is_Bit1_Clear()) {
				profile = PlayerProfile::Load(g_NickName);
			} else {
				profile = g_PlayerProfile.Get();
			}
			profile->SetLocale(users->locale, 2);
			if (options.Is_Bit1_Clear()) {
				profile->Save(&g_NickName);
			}
			DebugString("OnUserLocale callback - Locale is %d\n", users->locale);
			found = true;
		}
		user = user->next;
	}
	if (found) {
		SetEvent(g_WaitEventHandles[EV_LOCALE]);
	}
	return(S_OK);
}
