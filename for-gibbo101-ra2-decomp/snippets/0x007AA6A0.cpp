// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007AA6A0 (47 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x350660 (VA 0x00750660, 48 bytes incl. padding)
// RA2 symbol : ?OnSystemMessage@CChatEventSink@@UAGJJPBD@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9677)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

STDMETHODIMP CChatEventSink::OnSystemMessage(HRESULT res, LPCSTR message)
{
	if (!g_PlayingNetGame && res >= 0) {
		Lobby_Chat_Printf(g_SystemMessageColor, L">>> %hs", message);
	}
	return(S_OK);
}
