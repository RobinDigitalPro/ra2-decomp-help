// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006C8F10 (133 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x28fd90 (VA 0x0068FD90, 144 bytes incl. padding)
// RA2 symbol : ?STL_Score_Format_Time@@YIXPAUHWND__@@HH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9043)
// source TU  : src/ra2/unnamed/TU_68FB10.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall STL_Score_Format_Time(HWND dialog, int id, int seconds)   // 0x68fd90
{
    wchar_t text[32];
    int minutes = seconds / 60;
    int hours = minutes / 60;
    swprintf(text, L"%02d:%02d:%02d", hours, minutes - hours * 60, seconds - minutes * 60);
    HWND item = GetDlgItem(dialog, id);
    SendMessageA(item, 0x4b2, 0, (LPARAM)text);
}
