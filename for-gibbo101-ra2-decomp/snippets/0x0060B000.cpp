// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0060B000 (463 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1e0f80 (VA 0x005E0F80, 464 bytes incl. padding)
// RA2 symbol : ?Move_Free_Button@OwnerDraw@@YIXPAUHWND__@@ABVPoint2D@@@Z
// similarity : 0.9940 (very-similar, masked instruction tokens; shape 0.9970)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Move_Free_Button(HWND window, Point2D const &size) // RA2: as above
{
    HWND parent = GetParent(window);
    unsigned char flag = Session.Is_In_Game(); // RA2: as above
    RECT parent_rect;
    RECT rect;
    GetWindowRect(parent, &parent_rect); // RA2: as above
    GetWindowRect(window, &rect); // RA2: as above
    Rect area(parent_rect.left, parent_rect.top, parent_rect.right - parent_rect.left, parent_rect.bottom - parent_rect.top); // RA2: as above
    int offset = 0; // RA2: as above
    if (!flag) { // RA2: as above
        offset = (area.Width - Base_Screen_Width) / 2; // RA2: as above
        offset = offset < 0 ? 0 : offset; // RA2: as above
    }
    Rect area2(parent_rect.left, parent_rect.top, parent_rect.right - parent_rect.left, parent_rect.bottom - parent_rect.top); // RA2: as above
    int shift = 0; // RA2: as above
    if (!flag) { // RA2: as above
        shift = (((area2.Height - Base_Screen_Height) / 2) < 0 ? 0 : ((area2.Height - Base_Screen_Height) / 2)); // RA2: as above
        shift -= (((size.Y - Base_Screen_Height) / 2) < 0 ? 0 : ((size.Y - Base_Screen_Height) / 2)); // RA2: as above
    }
    int x;
    int y;
    int width; // RA2: as above
    int height; // RA2: as above
    if (flag) { // RA2: as above
        width = Button_Strip_Shape->Get_Width(); // RA2: as above
        height = Button_Strip_Shape->Get_Height(); // RA2: as above
        Rect *strip = Free_Button_Strip; // RA2: as above
        x = parent_rect.right - offset - parent_rect.left - 0x93; // RA2: as above
        HWND dialog = GetParent(window); // RA2: as above
        RECT parent2; // RA2: as above
        RECT rect2;
        GetWindowRect(dialog, &parent2); // RA2: as above
        GetWindowRect(window, &rect2);
        int top = rect2.top - parent2.top; // RA2: as above
        y = ((rect2.bottom - parent2.top - top) / 2 - 0xc6 + top) / 0x2c * height + strip->Y; // RA2: as above
    } else {
        width = Slide_Button_Shape->Get_Width(); // RA2: as above
        height = Slide_Button_Shape->Get_Height(); // RA2: as above
        Rect *strip = Button_Strip_Top; // RA2: as above
        x = parent_rect.right - offset - parent_rect.left - 0x9c; // RA2: as above
        int top = strip->Y; // RA2: as above
        int pos = rect.top - top - parent_rect.top + shift; // RA2: as above
        int row = pos / strip->Height; // RA2: as above
        int prod = strip->Height * row; // RA2: as above
        int up = abs(strip->Height - pos + prod); // RA2: as above
        int down = abs(pos - prod); // RA2: as above
        y = (down < up ? row : row + 1) * strip->Height + top; // RA2: as above
    }
    MoveWindow(window, x, y, width, height, FALSE); // RA2: as above
}
