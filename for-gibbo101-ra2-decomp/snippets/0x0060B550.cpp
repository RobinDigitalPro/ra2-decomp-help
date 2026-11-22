// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0060B550 (182 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1e14e0 (VA 0x005E14E0, 192 bytes incl. padding)
// RA2 symbol : ?Move_Flag_Control@OwnerDraw@@YIXPAUHWND__@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9351)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Move_Flag_Control(HWND window) // RA2: as above
{
    HWND parent = GetParent(window);
    unsigned char flag = Session.Is_In_Game(); // RA2: as above
    RECT parent_rect;
    RECT rect;
    GetClientRect(parent, &parent_rect); // RA2: as above
    GetWindowRect(window, &rect); // RA2: as above
    int left = parent_rect.left; // RA2: as above
    Rect area(left, parent_rect.top, parent_rect.right - left, parent_rect.bottom - parent_rect.top); // RA2: as above
    int offset = 0; // RA2: as above
    if (!flag) { // RA2: as above
        offset = (area.Width - Base_Screen_Width) / 2; // RA2: as above
        offset = offset < 0 ? 0 : offset; // RA2: as above
    }
    Rect area2(parent_rect.left, parent_rect.top, parent_rect.right - parent_rect.left, parent_rect.bottom - parent_rect.top); // RA2: as above
    int shift = 0; // RA2: as above
    if (!flag) { // RA2: as above
        shift = (area2.Height - Base_Screen_Height) / 2; // RA2: as above
        shift = shift < 0 ? 0 : shift; // RA2: as above
    }
    int width = rect.right - rect.left; // RA2: as above
    int height = rect.bottom - rect.top; // RA2: as above
    MoveWindow(window, offset + 10 + left, parent_rect.bottom - shift - height - 1, width, height, FALSE); // RA2: as above
}
