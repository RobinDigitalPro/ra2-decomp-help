// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E23A0 (34 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1bd4d0 (VA 0x005BD4D0, 48 bytes incl. padding)
// RA2 symbol : ?Host_Clear_Start_Button@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5882)
// source TU  : src/ra2/netdlg2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x5bd4d0
void Host_Clear_Start_Button()
{
    HWND dialog = Current_Dialog();
    HWND item = GetDlgItem(dialog, 0x59f);
    SendMessageA(item, 0x4dc, 0, 0);
}
