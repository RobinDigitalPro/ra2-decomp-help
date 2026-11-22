// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0077DB90 (253 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x330f50 (VA 0x00730F50, 256 bytes incl. padding)
// RA2 symbol : ?Send_Player_List@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9806)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Send_Player_List(void) // RA2: 0x0073C480, sends the names of the eight slots (the lobby entry names for open and AI slots) as game option L
{
	char text[256];
	strcpy(text, "L"); // RA2: as above
	for (int i = 0; i < 8; ++i) { // RA2: as above
		NodeNameType * entry = Session.Slots[i]; // RA2: as above
		Wstring name;
		if (Is_Real_Player_Entry(entry)) { // RA2: as above
			name = Wstring_Narrow(entry->Name); // RA2: as above
		} else {
			name = Lobby_Entry_Name(entry); // RA2: as above
		}
		strncat(text, name.get(), 256); // RA2: as above
		strncat(text, ",", 256); // RA2: as above
	}
	g_pChat->RequestPublicGameOptions(text); // RA2: as above
}
