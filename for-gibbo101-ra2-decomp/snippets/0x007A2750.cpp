// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007A2750 (114 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x34a170 (VA 0x0074A170, 128 bytes incl. padding)
// RA2 symbol : ?Wol_Handle_Start_Reminder@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8409)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Wol_Handle_Start_Reminder(void) // RA2: 0x0075C980 (1.001 0x0074A170), the joiner is told to accept
{
	HWND dialog = WS_Top_Window();
	HWND item = GetDlgItem(dialog, 0x59F);
	bool joiner;
	{
		Wstring host((char const *)NULL);
		joiner = GetPlayerAccepted(host) != 1;
	}
	if (joiner) {
		SendMessage(item, 0x4DC, 0, 1);
		Lobby_Chat_Printf(-1, StringTable::LoadString("GUI:HostGameStartJoiner", NULL, "C:\\RA2\\wonline.cpp", 19955)); // level-2 1.001: line literal
	}
}
