// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0060AF50 (173 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1e0ed0 (VA 0x005E0ED0, 176 bytes incl. padding)
// RA2 symbol : ?Move_Control_To_Rect@OwnerDraw@@YIXPAUHWND__@@ABV?$TRect@H@@@Z
// similarity : 0.9710 (very-similar, masked instruction tokens; shape 0.8816)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Move_Control_To_Rect(HWND window, Rect const &rect) // RA2: as above
{
    HWND parent = GetParent(window);
    unsigned char flag = Session.Is_In_Game(); // RA2: as above
    RECT parent_rect;
    GetWindowRect(parent, &parent_rect); // RA2: as above
    Rect area(parent_rect.left, parent_rect.top, parent_rect.right - parent_rect.left, parent_rect.bottom - parent_rect.top); // RA2: as above
    int offset = 0; // RA2: as above
    if (!flag) { // RA2: as above
        offset = (((area.Width - Base_Screen_Width) / 2) < 0 ? 0 : ((area.Width - Base_Screen_Width) / 2)); // RA2: as above
    }
    Rect area2(parent_rect.left, parent_rect.top, parent_rect.right - parent_rect.left, parent_rect.bottom - parent_rect.top); // RA2: as above
    int shift = 0; // RA2: as above
    if (!flag) { // RA2: as above
        shift = (((area2.Height - Base_Screen_Height) / 2) < 0 ? 0 : ((area2.Height - Base_Screen_Height) / 2)); // RA2: as above
    }
    MoveWindow(window, rect.X + offset, rect.Y + shift, rect.Width, rect.Height, FALSE); // RA2: as above
}
