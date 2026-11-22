// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005C9850 (67 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1a7770 (VA 0x005A7770, 80 bytes incl. padding)
// RA2 symbol : ?Set_Dialog_Number@@YIXPAUHWND__@@HH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7937)
// source TU  : src/ra2/MPScore.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x5a7770 (no direct callers; inlined four times into MPScore_Dialog_Proc)
void Set_Dialog_Number(HWND dialog, int id, int value)
{
    wchar_t buffer[32];
    swprintf(buffer, L"%d", value);
    HWND item = GetDlgItem(dialog, id);
    SendMessageA(item, WM_SET_TEXT_WIDE, 0, (LPARAM)buffer);
}
