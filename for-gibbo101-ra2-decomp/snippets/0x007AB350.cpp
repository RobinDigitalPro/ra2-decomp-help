// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007AB350 (108 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x350e60 (VA 0x00750E60, 112 bytes incl. padding)
// RA2 symbol : ?OnServerBannedYou@CChatEventSink@@UAGJJJ@Z
// similarity : 0.9667 (very-similar, masked instruction tokens; shape 0.9375)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

STDMETHODIMP CChatEventSink::OnServerBannedYou(HRESULT res, time_t bannedTill)
{
	wchar_t text[200];
	if (!g_PlayingNetGame && res == 0) {
		swprintf(text, StringTable::LoadString("TXT_BANNEDTILL", NULL, "C:\\RA2\\wonline.cpp", 6386), ctime(&bannedTill));
		ODMessageBox(text, 0, Wait_Callback_Thunk, false);
	}
	return(S_OK);
}
