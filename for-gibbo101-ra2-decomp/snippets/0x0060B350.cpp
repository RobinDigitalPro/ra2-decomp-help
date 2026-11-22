// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0060B350 (206 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1e12d0 (VA 0x005E12D0, 208 bytes incl. padding)
// RA2 symbol : ?Move_Default_Button_Owner@OwnerDraw@@YIXPAUHWND__@@@Z
// similarity : 0.9605 (very-similar, masked instruction tokens; shape 0.9870)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Move_Default_Button_Owner(HWND window) // RA2: as above
{
    HWND parent = GetParent(window);
    unsigned char flag = Session.Is_In_Game(); // RA2: as above
    RECT parent_rect;
    RECT rect;
    GetWindowRect(parent, &parent_rect); // RA2: as above
    GetWindowRect(window, &rect); // RA2: as above
    Rect area(parent_rect.left, parent_rect.top, parent_rect.right - parent_rect.left, parent_rect.bottom - parent_rect.top); // RA2: as above
    int offset = Sidebar_Inset(area.Width, flag); // RA2: as above
    int x;
    int y;
    int width; // RA2: as above
    int height; // RA2: as above
    if (flag) { // RA2: as above
        x = parent_rect.right - offset - parent_rect.left - 0x93; // RA2: as above
        width = Button_Strip_Shape->Get_Width(); // RA2: as above
        height = Button_Strip_Shape->Get_Height(); // RA2: as above
        y = Default_Button_Y->Y - height; // RA2: as above
    } else {
        width = Slide_Button_Shape->Get_Width(); // RA2: as above
        x = parent_rect.right - offset - parent_rect.left - 0x9c; // RA2: as above
        height = Slide_Button_Shape->Get_Height(); // RA2: as above
        int top = Button_Strip_Top->Y; // RA2: as above
        int cell = Button_Strip_Top->Height; // RA2: as above
        y = ((Button_Strip_Bottom->Y - top) / cell - 1) * cell + top; // RA2: as above
    }
    MoveWindow(window, x, y, width, height, FALSE); // RA2: as above
}
