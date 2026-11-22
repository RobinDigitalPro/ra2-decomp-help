// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004E49A0 (635 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xd1bb0 (VA 0x004D1BB0, 592 bytes incl. padding)
// RA2 symbol : ?Select_Color@@YIXPAUHWND__@@HH@Z
// similarity : 0.9590 (very-similar, masked instruction tokens; shape 0.9447)
// source TU  : src/ra2/GDlgSupp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Select_Color(HWND dialog, int id, int color)
{
    HWND list = GetDlgItem(dialog, id);
    bool hidden = (ShowWindow(list, SW_HIDE) == 0);

    int old = Combo_Color(id);
    if (old != -1) {
        PlayerColors[old].Owner = -1;
    }

    int count = SendDlgItemMessageA(dialog, id, CB_GETCOUNT, 0, 0);
    for (int index = 0; index < count; index++) {
        int data = SendDlgItemMessageA(dialog, id, CB_GETITEMDATA, index, 0);
        if (data == color) {
            SendDlgItemMessageA(dialog, id, CB_SETCURSEL, index, 0);
            if (data != COLOR_RANDOM) {
                PlayerColors[data].Owner = Player_Color_Slot(id);
            }
            break;
        }
    }
    if (!hidden) {
        ShowWindow(list, SW_SHOW);
    }
    Fill_All_Color_Lists(dialog);
}
