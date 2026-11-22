// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00798F50 (290 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x3415d0 (VA 0x007415D0, 304 bytes incl. padding)
// RA2 symbol : ?Fill_Locale_Combo@@YIXPAUHWND__@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9320)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Fill_Locale_Combo(HWND combo) // RA2: 1.001 0x007415D0, fills a combo box with the locale names (the first two inserted at the top) and selects the persona's locale
{
	Clear_ComboBox(combo);
	int count = 0;
	g_pChat->GetLocaleCount(&count);
	WOLOptionsClass options;
	options.Load();
	rc_ptr<PlayerProfile> profile;
	if (options.Is_Bit1_Clear()) {
		profile = PlayerProfile::Load(g_NickName);
	} else {
		profile = g_PlayerProfile.Get();
	}
	if (count > 0) {
		for (int i = count - 1; i >= 0; i--) {
			WideWstring name = Get_Locale_Name(i);
			int item;
			if (i < 2) {
				item = SendMessage(combo, 0x4C1, 0, (LPARAM)name.get());
			} else {
				item = SendMessage(combo, 0x4C2, 0, (LPARAM)name.get());
			}
			SendMessage(combo, CB_SETITEMDATA, item, i);
			if (profile.Get() && i == profile->Locale) {
				SendMessage(combo, CB_SETCURSEL, item, 0);
			}
		}
	}
}
