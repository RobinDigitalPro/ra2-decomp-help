// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0060F320 (385 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1e4c10 (VA 0x005E4C10, 400 bytes incl. padding)
// RA2 symbol : ?Replace_Edit@OwnerDraw@@YGHPAUHWND__@@J@Z
// similarity : 0.9926 (very-similar, masked instruction tokens; shape 0.9474)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

BOOL __stdcall Replace_Edit(HWND window, LPARAM) // RA2: as above
{
    unsigned int style = GetWindowLongA(window, GWL_STYLE); // RA2: as above
    SetWindowLongA(window, -21, 0); // RA2: as above
    if ((style & 0x10000000) && !(style & 0x08000000)) { // RA2: as above
        char name[128]; // RA2: as above
        GetClassNameA(window, name, sizeof(name)); // RA2: as above
        if (strcmp(name, "Edit") == 0) { // RA2: as above
            HWND parent = GetParent(window);
            RECT rect;
            RECT parent_rect;
            Get_Display_Rect(window, &rect);
            Get_Display_Rect(parent, &parent_rect);
            int x = rect.left - parent_rect.left; // RA2: as above
            int y = rect.top - parent_rect.top; // RA2: as above
            DWORD list_style = 0x40000110; // RA2: as above
            if (style & 0x10000) { // RA2: as above
                list_style = 0x40010110; // RA2: as above
            }
            HWND list = CreateWindowExA(0, "ListBox", 0, list_style, x, y, // RA2: as above
                                        rect.right - rect.left, rect.bottom - rect.top, parent, 0, ProgramInstance, 0); // RA2: as above
            LONG *data = (LONG *)operator new(8); // RA2: as above
            data[0] = (LONG)"NewEdit"; // RA2: as above
            data[1] = GetWindowLongA(window, GWL_STYLE); // RA2: as above
            SetWindowLongA(list, -21, (LONG)data); // RA2: as above
            EnableWindow(window, FALSE); // RA2: as above
            ShowWindow(window, SW_HIDE); // RA2: as above
            EnableWindow(list, TRUE); // RA2: as above
            ShowWindow(list, SW_SHOWNORMAL); // RA2: as above
            LONG id = GetWindowLongA(window, -12); // RA2: as above
            SetWindowLongA(window, -12, GetWindowLongA(list, -12)); // RA2: as above
            SetWindowLongA(list, -12, id); // RA2: as above
        }
    }
    return TRUE; // RA2: as above
}
