// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0079DA90 (192 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x345eb0 (VA 0x00745EB0, 192 bytes incl. padding)
// RA2 symbol : ?Buddy_Name_From_List@@YI?AVWstring@@PAUHWND__@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

Wstring Buddy_Name_From_List(HWND list) // RA2: 1.001 0x00745EB0, the name in parentheses of the first row from the selection on, else the selected buddy
{
	int index = SendMessage(list, LB_GETCURSEL, 0, 0);
	if (index == -1) {
		index = 0;
	}
	while (index < SendMessage(list, LB_GETCOUNT, 0, 0)) {
		WideWstring text;
		Get_List_Item_Wide_Text(list, index, text);
		if (text.getChar(0) == L'(' && text.truncate(L')')) {
			text.removeChar(L'(');
			return(Wstring_Narrow(text));
		}
		index++;
	}
	return(g_SelectedBuddy);
}
