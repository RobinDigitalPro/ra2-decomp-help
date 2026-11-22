// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0079BF50 (231 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x344390 (VA 0x00744390, 240 bytes incl. padding)
// RA2 symbol : ?Update_Buddy_Buttons@@YIXPAUHWND__@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9497)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Update_Buddy_Buttons(HWND dialog) // RA2: 1.001 0x00744390, enables the buttons of the buddy dialog
{
	EnableWindow(GetDlgItem(dialog, 0x703), g_SelectedBuddy.length() > 0);
	EnableWindow(GetDlgItem(dialog, 0x62D), Can_Join_Buddy_Game());
	EnableWindow(GetDlgItem(dialog, 0x5C2), Is_Selected_Buddy_Known());
}
