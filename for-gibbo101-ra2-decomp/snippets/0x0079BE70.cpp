// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0079BE70 (89 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x3442b0 (VA 0x007442B0, 96 bytes incl. padding)
// RA2 symbol : ?Open_Buddy_Page_Dialog@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8889)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Open_Buddy_Page_Dialog(void) // RA2: 1.001 0x007442B0, opens the dialog (0x11E) and waits for it
{
	HWND dialog = WS_Create_Dialog(ProgramInstance, 0x11E, MainWindow, WOL_Page_Reply_Dialog_Proc, 0);
	Show_Dialog(dialog, 0x11E);
	SendMessage(dialog, 0x4A9, 0, 1);
	ShowWindow(dialog, SW_SHOWNORMAL);
	WS_Wait_Dialog(dialog, WOL_Wait_Callback);
}
