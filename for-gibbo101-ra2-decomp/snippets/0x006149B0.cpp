// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006149B0 (373 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1ea1e0 (VA 0x005EA1E0, 384 bytes incl. padding)
// RA2 symbol : ?Edit_Text@OwnerDraw@@YIHPAUHWND__@@PAGHPAH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9611)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __fastcall Edit_Text(HWND window, wchar_t *text, int size, int *caret) // RA2: as above
{
    WNDPROC proc = 0; // RA2: as above
    Window_Proc_Table.getValue(window, proc); // RA2: as above
    char buffer[1024]; // RA2: as above
    int start = 0; // RA2: as above
    buffer[0] = 0; // RA2: as above
    CallWindowProcA(proc, window, WM_GETTEXT, sizeof(buffer), (LPARAM)buffer); // RA2: as above
    if (caret) { // RA2: as above
        DWORD selection_start; // RA2: as above
        DWORD selection_end; // RA2: as above
        start = (unsigned long)CallWindowProcA(proc, window, EM_GETSEL, (WPARAM)&selection_start, (LPARAM)&selection_end) >> 16; // RA2: as above
    }
    *text = 0;
    MultiByteToWideChar(0, 0, buffer, -1, text, size); // RA2: as above
    if (caret) { // RA2: as above
        *caret = _mbsnbcnt((unsigned char *)buffer, start);
    }
    if (size > 0) { // RA2: as above
        text[size - 1] = 0; // RA2: as above
    }
    int length = wcslen(text); // RA2: as above
    wchar_t *copy = new wchar_t[length + 3]; // RA2: as above
    memset(copy, 0, (length + 3) * sizeof(wchar_t)); // RA2: as above
    int count = 0; // RA2: as above
    int i = 0;
    for (; i < length; i++) { // RA2: as above
        if (text[i] != '\r' && text[i] != '\n') { // RA2: as above
            copy[count++] = text[i]; // RA2: as above
        }
    }
    if (i != count) { // RA2: as above
        wcscat(copy, L"\r\n"); // RA2: as above
    }
    wcscpy(text, copy); // RA2: as above
    delete[] copy; // RA2: as above
    return wcslen(text); // RA2: as above
}
