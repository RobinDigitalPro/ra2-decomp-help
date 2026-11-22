// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0077A8D0 (279 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x32e610 (VA 0x0072E610, 288 bytes incl. padding)
// RA2 symbol : ?Clear_Dialog@PlayerProfile@@SIXPAUHWND__@@_N@Z
// similarity : 0.9902 (very-similar, masked instruction tokens; shape 0.9577)
// source TU  : src/ra2/WOLPersonaInformation.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x32e610
void PlayerProfile::Clear_Dialog(HWND dialog, bool clear_name)
{
    if (clear_name) {
        HWND combo = GetDlgItem(dialog, IDC_PERSONA_NAME);
        SendMessageA(combo, WM_SET_TEXT_NARROW, 0, (LPARAM)NullString);
        InvalidateRect(combo, NULL, FALSE);
    }
    Set_Item_Text(GetDlgItem(dialog, IDC_PERSONA_LABEL), NullWString);
#line 639 "C:\\RA2\\WOLPersonaInformation.cpp"
    WideStringClass unknown(Fetch_String("GUI:UnknownStats", NULL, __FILE__, __LINE__));
    Set_Item_Text(GetDlgItem(dialog, IDC_PERSONA_WINS), unknown);
    Set_Item_Text(GetDlgItem(dialog, IDC_PERSONA_LOSSES), unknown);
    Set_Item_Text(GetDlgItem(dialog, IDC_PERSONA_DISCONNECTS), unknown);
    Set_Item_Text(GetDlgItem(dialog, IDC_PERSONA_RANK), unknown);
    Set_Item_Text(GetDlgItem(dialog, IDC_PERSONA_POINTS), unknown);
}
