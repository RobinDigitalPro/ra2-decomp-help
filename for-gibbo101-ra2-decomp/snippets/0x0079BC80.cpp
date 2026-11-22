// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0079BC80 (486 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x3440d0 (VA 0x007440D0, 480 bytes incl. padding)
// RA2 symbol : ?Can_Join_Buddy_Game@@YI_NXZ
// similarity : 0.9821 (very-similar, masked instruction tokens; shape 0.9708)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool Can_Join_Buddy_Game(void) // RA2: 1.001 0x007440D0, the selected buddy is in a game the player may join
{
	if (g_SelectedBuddy.length() == 0) {
		return(false);
	}
	unsigned int state = 0;
	g_BuddyStatus.getValue(g_SelectedBuddy, state);
	if (state == 4) {
		return(true);
	}
	if (state != 5) {
		return(false);
	}
	Channel channel;
	if (!g_BuddyChannels.getValue(g_SelectedBuddy, channel)) {
		return(false);
	}
	Wstring game_name((char *)channel.name);
	Channel game;
	if (!Find_Channel(game_name, g_GameChannelList, game)) {
		return(false);
	}
	return(Can_Join_Channel(&game, false));
}
