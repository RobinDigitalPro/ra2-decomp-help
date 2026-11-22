// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007A16B0 (807 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x3494b0 (VA 0x007494B0, 816 bytes incl. padding)
// RA2 symbol : ?Process_Match_Message@@YIXPBD_N@Z
// similarity : 0.9920 (very-similar, masked instruction tokens; shape 0.9823)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Process_Match_Message(char const * message, bool is_private) // RA2: 1.001 0x007494B0, a message of the matching server (the private ones may fail or start the match)
{
	if (is_private && Match_Failed(message)) {
		return;
	}
	if (strnicmp(message, "Exit", 4) == 0) {
		Lobby_Chat_Printf(0x40FFFF, StringTable::LoadString("WOL:MatchFailExit", NULL, "C:\\RA2\\wonline.cpp", 19554));
		g_pChat->RequestChannelLeave();
		ODMessageBox(StringTable::LoadString("WOL:MatchFailExit", NULL, "C:\\RA2\\wonline.cpp", 19557), 0, Wait_Callback_Thunk, false);
		SetEvent(g_WaitEventHandles[EV_ABORT]);
		return;
	}
	if (strnicmp(message, "Working", 7) == 0) {
		if (g_MatchState == 4) {
			Set_Match_State(5, 180, 0);
		}
		Lobby_Chat_Printf(ColorSystem, StringTable::LoadString("GUI:MatchingProgress2", NULL, "C:\\RA2\\wonline.cpp", 19569));
		return;
	}
	if (strnicmp(message, "Info ", 5) == 0) {
		Lobby_Chat_Printf(0xFF8080, Narrow_To_Wide(message + 5));
		return;
	}
	if (strnicmp(message, "Pool ", 5) == 0) {
		message += 5;
		Lobby_Chat_Printf(0xFF8080, StringTable::LoadString("WOL:MatchingPlayerPool", NULL, "C:\\RA2\\wonline.cpp", 19579), message);
		return;
	}
	if (is_private && strnicmp(message, "Start ", 6) == 0) {
		message += 6;
		strncpy(g_MatchStartOptions, message, 0xFF);
		DebugString("%s\n", g_MatchStartOptions);
		SetEvent(g_WaitEventHandles[EV_16]);
		return;
	}
	if (stricmp(message, "ack") == 0 || stricmp(message, "nack") == 0) {
		return;
	}
	if (strnicmp(message, "need ", 5) == 0) {
		DebugString("%s\n", message);
		return;
	}
	if (is_private) {
		Lobby_Chat_Printf(0x40FFFF, StringTable::LoadString("WOL:MatchUnknownServerCommand", NULL, "C:\\RA2\\wonline.cpp", 19612));
	}
}
