// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0079C040 (853 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x344480 (VA 0x00744480, 864 bytes incl. padding)
// RA2 symbol : ?Update_Buddy_Profile_Labels@@YIXPAUHWND__@@@Z
// similarity : 0.9925 (very-similar, masked instruction tokens; shape 0.9797)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Update_Buddy_Profile_Labels(HWND dialog) // RA2: 1.001 0x00744480, the labels of the buddy dialog: the name of the selected buddy and its ladder entry (or the unknown text)
{
	HWND name_label = GetDlgItem(dialog, 0x6EF);
	HWND rung_label = GetDlgItem(dialog, 0x6F4);
	HWND points_label = GetDlgItem(dialog, 0x6F5);
	HWND wins_label = GetDlgItem(dialog, 0x6F0);
	HWND losses_label = GetDlgItem(dialog, 0x6F1);
	HWND disconnects_label = GetDlgItem(dialog, 0x701);
	if (g_SelectedBuddy.length() == 0) {
		SendMessage(name_label, 0x4B2, 0, (LPARAM)NullWString);
		SendMessage(rung_label, 0x4B2, 0, (LPARAM)NullWString);
		SendMessage(points_label, 0x4B2, 0, (LPARAM)NullWString);
		SendMessage(wins_label, 0x4B2, 0, (LPARAM)NullWString);
		SendMessage(losses_label, 0x4B2, 0, (LPARAM)NullWString);
		SendMessage(disconnects_label, 0x4B2, 0, (LPARAM)NullWString);
		return;
	}
	WideWstring format(StringTable::LoadString("GUI:UserProfileLabel", NULL, "C:\\RA2\\wonline.cpp", 17970)); // level-2 1.001: line literal
	wchar_t * text = new wchar_t[format.length() + g_SelectedBuddy.length() + 1];
	swprintf(text, format.get(), g_SelectedBuddy.get());
	HWND name_item = GetDlgItem(dialog, 0x6EF);
	SendMessage(name_item, 0x4B2, 0, (LPARAM)text);
	delete text;
	Ladder ladder;
	memset(&ladder, 0, sizeof(ladder));
	Wstring key = ((Wstring const &)g_SelectedBuddy).toLower();
	if (g_GeneralLadderDict.getValue(key, ladder)) {
		Set_Label_Text(rung_label, WideWstring_FromInt(ladder.rung).text());
		Set_Label_Text(points_label, WideWstring_FromInt(ladder.points).text());
		Set_Label_Text(wins_label, WideWstring_FromInt(ladder.wins).text());
		Set_Label_Text(losses_label, WideWstring_FromInt(ladder.losses).text());
		Set_Label_Text(disconnects_label, WideWstring_FromInt(ladder.disconnects).text());
	} else {
		WideWstring unknown(StringTable::LoadString("GUI:UnknownStats", NULL, "C:\\RA2\\wonline.cpp", 17987)); // level-2 1.001: line literal
		Set_Label_Text(rung_label, unknown.text());
		Set_Label_Text(points_label, unknown.text());
		Set_Label_Text(wins_label, unknown.text());
		Set_Label_Text(losses_label, unknown.text());
		Set_Label_Text(disconnects_label, unknown.text());
	}
}
