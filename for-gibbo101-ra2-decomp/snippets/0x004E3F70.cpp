// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004E3F70 (497 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xd1310 (VA 0x004D1310, 480 bytes incl. padding)
// RA2 symbol : ?Select_Side@@YIXPAUHWND__@@HH@Z
// similarity : 0.9655 (very-similar, masked instruction tokens; shape 0.9222)
// source TU  : src/ra2/GDlgSupp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Select_Side(HWND dialog, int id, int side)
{
    HWND list = GetDlgItem(dialog, id);
    bool hidden = (ShowWindow(list, SW_HIDE) == 0);
    int count = SendDlgItemMessageA(dialog, id, CB_GETCOUNT, 0, 0);
    for (int index = 0; index < count; index++) {
        if (SendDlgItemMessageA(dialog, id, CB_GETITEMDATA, index, 0) == side) {
            SendDlgItemMessageA(dialog, id, CB_SETCURSEL, index, 0);
            break;
        }
    }
    if (!hidden) {
        ShowWindow(list, SW_SHOW);
    }
    Update_Player_Flag(dialog, Player_Side_Slot(id));
}
