// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00780A90 (758 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x333a40 (VA 0x00733A40, 768 bytes incl. padding)
// RA2 symbol : ?User_Tooltip@@YI?AVWideWstring@@ABUUser@@@Z
// similarity : 0.9866 (very-similar, masked instruction tokens; shape 0.9782)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

WideWstring User_Tooltip(User const & user) // RA2: 0x0073F250, the text of the tooltip of a lobby user: name, rank in the active ladder, squad and locale
{
	Wstring name((char *)user.name); // RA2: as above
	WideWstring text = Wstring_ToWide(name) + L" : "; // RA2: as above
	name.toLower();
	Ladder ladder;
	memset(&ladder, 0, sizeof(ladder));
	if (g_ActiveLadder && g_ActiveLadder->getValue(name, ladder)) { // RA2: as above
		text += WideWstring(StringTable::LoadString("TXT_RANK", NULL, "C:\\RA2\\wonline.cpp", 2373)) + WideWstring(L" ") + WideWstring_FromInt(ladder.rung); // RA2: as above // level-2 1.001: line literal
	} else {
		text += StringTable::LoadString("TXT_UNRANKED", NULL, "C:\\RA2\\wonline.cpp", 2375); // RA2: as above // level-2 1.001: line literal
	}
	Wstring squad((char *)user.squadname); // RA2: as above
	if (squad.length() == 0) squad = (char *)user.squadabbrev; // RA2: the abbreviation stands for a squad without a name
	if (squad.length() > 0) {
		text += L": " + Wstring_ToWide(squad); // RA2: as above
	}
	if (g_UserLocales.contains(name)) { // RA2: as above
		int * locale = 0;
		if (g_pChat && g_UserLocales.getPointer(name, &locale) && locale && *locale) { // RA2: as above
			text += L" : " + Get_Locale_Name(*locale); // RA2: as above
		}
	}
	return(text);
}
