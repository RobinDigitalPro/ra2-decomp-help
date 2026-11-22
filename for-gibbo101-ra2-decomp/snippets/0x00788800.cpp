// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00788800 (552 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x338b50 (VA 0x00738B50, 560 bytes incl. padding)
// RA2 symbol : ?Request_Channel_Join@@YIHPAUChannel@@ABVWstring@@VWideWstring@@@Z
// similarity : 0.9620 (very-similar, masked instruction tokens; shape 0.9787)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int Request_Channel_Join(Channel * channel, Wstring const & password, WideWstring title) // RA2: 0x00744700, not in TibSun: joins a channel (leaves the current one first); title is the text of the wait dialog; the chat's answer, 1 when the old channel could not be left
{
	char const * name = (char const *)channel->name; // RA2: as above
	if (strcmp(name, (char const *)g_CurrentChannel.name) && strcmp(name, (char const *)g_PendingChannel.name)) { // RA2: not the channel the chat is in nor the one it was asked to join
		if (g_ChannelCount) { // RA2: as Leave_Current_Channel
			DebugString("Leave_Channel, channel %s type %d\n", g_CurrentChannel.name, g_CurrentChannel.type); // RA2: as above
			g_pChat->RequestChannelLeave(); // RA2: as above
			{
				WideWstring leaving(StringTable::LoadString("WOL:LeavingChannel", NULL, "C:\\RA2\\wonline.cpp", 8207)); // RA2: as above // level-2 1.001: line literal
				Show_Wait_Window(0x40, leaving, true); // RA2: as above
			}
			for (int i = 0; g_ChannelCount && i < 150; i++) { // RA2: as above
				Sleep(100); // RA2: as above
				WOL_Wait_Callback(); // RA2: as above
			}
			Close_Wait_Window(0x40); // RA2: expanded here
			if (g_ChannelCount) { // RA2: the channel was not left
				return(1); // RA2: as above
			}
		}
		strcpy((char *)channel->key, password.text()); // RA2: as above
		g_PendingChannel = *channel; // RA2: as above
		{
			WideWstring message(title.text()); // RA2: as above
			Show_Wait_Window(2, message, false); // RA2: as above
		}
		DebugString("Requesting channel join %s\n", name); // RA2: as above
		return g_pChat->RequestChannelJoin(channel); // RA2: virtual 0x20
	}
	return(0); // RA2: as above
}
