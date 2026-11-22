// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00786DC0 (164 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x337340 (VA 0x00737340, 176 bytes incl. padding)
// RA2 symbol : ?Recall_Stored_Login@@YI_NABVWstring@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9118)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool Recall_Stored_Login(Wstring const & name) // RA2: 0x00742D80, not in TibSun: looks the persona up among the 32 logins the chat API remembers; keeps its nickname and password when it is there, else clears the nickname
{
	g_LoginPassword.clear(); // RA2: as above
	for (int index = 1; index <= 32; index++) { // RA2: as above
		char const * nickname; // RA2: not cleared, the chat API sets both when it succeeds
		char const * password; // RA2: as above
		if (g_pChat->GetNick(index, &nickname, &password) == 0 && nickname && strlen(nickname) && !stricmp(name.text(), nickname)) { // RA2: as above
			g_NickName = nickname; // RA2: as above
			g_LoginPassword = password; // RA2: as above
			g_PlaintextPassword = false; // RA2: as above
			return(true); // RA2: as above
		}
	}
	g_NickName.clear(); // RA2: as above
	return(false); // RA2: as above
}
