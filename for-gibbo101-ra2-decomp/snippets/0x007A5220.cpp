// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007A5220 (22 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x34c460 (VA 0x0074C460, 32 bytes incl. padding)
// RA2 symbol : ?OnLogout@CChatEventSink@@UAGJJPAUUser@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5833)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

STDMETHODIMP CChatEventSink::OnLogout(HRESULT status, User *user)
{
	if (status >= 0) {
		Handle_User_Leave(*user);
	}
	return(S_OK);
}
