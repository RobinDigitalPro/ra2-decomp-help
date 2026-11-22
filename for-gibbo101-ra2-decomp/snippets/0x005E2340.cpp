// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E2340 (83 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1bd470 (VA 0x005BD470, 96 bytes incl. padding)
// RA2 symbol : ?Host_Update_Start_Button@@YIXXZ
// similarity : 0.9615 (very-similar, masked instruction tokens; shape 0.8000)
// source TU  : src/ra2/netdlg2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x5bd470
void Host_Update_Start_Button()
{
    HWND dialog = Current_Dialog();
    HWND item = GetDlgItem(dialog, 0x59f);
    if (Player_Accept_State(NULL) != 1) {
        SendMessageA(item, 0x4dc, 0, 1);
#line 4655
        Lobby_Add_Message(-1, Fetch_String("GUI:HostGameStartJoiner", NULL, __FILE__, __LINE__));
    }
}
