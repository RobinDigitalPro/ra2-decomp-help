// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007A55F0 (145 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x34c840 (VA 0x0074C840, 160 bytes incl. padding)
// RA2 symbol : ?OnMessageOfTheDay@CChatEventSink@@UAGJJPBD@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8544)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

STDMETHODIMP CChatEventSink::OnMessageOfTheDay(HRESULT res, LPCSTR motd)
{
	wchar_t wide[1024];
	if (res < 0) {
		return(S_OK);
	}
	char * buffer = strdup(motd);
	char * line = strtok(buffer, "\n");
	while (line) {
		Char_To_Wide(wide, line, -1);
		Lobby_Chat_Printf(ColorSystem, wide);
		line = strtok(NULL, "\n");
	}
	free(buffer);
	Lobby_Chat_Printf(ColorSystem, L"\n");
	return(S_OK);
}
