// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007ABAF0 (586 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x3514b0 (VA 0x007514B0, 592 bytes incl. padding)
// RA2 symbol : ?OnSetLocale@CChatEventSink@@UAGJJW4Locale@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9837)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

STDMETHODIMP CChatEventSink::OnSetLocale(HRESULT res, Locale newlocale) // level-2 1.001: 0x007514B0, the server confirmed the persona's new locale: it replaces the entry in the locale dictionary (contains, remove and add all expanded)
{
	Wstring name;
	char handle[64];
	strcpy(handle, Session.Handle);
	name.set(handle);
	name.toLower();
	if (g_UserLocales.contains(name)) {
		g_UserLocales.remove(name);
	}
	int locale = newlocale;
	g_UserLocales.add(name, locale);
	return(S_OK);
}
