// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007AF6C0 (685 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x354b60 (VA 0x00754B60, 688 bytes incl. padding)
// RA2 symbol : ?Faction_Select_Dialog_Proc@@YGHPAUHWND__@@IIJ@Z
// similarity : 0.9666 (very-similar, masked instruction tokens; shape 0.9587)
// source TU  : src/ra2/WorldDom.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x354b60; the original __LINE__ values of the three Fetch_String calls are 176, 179 and 182.
static BOOL CALLBACK Faction_Select_Dialog_Proc(HWND dialog, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_INITDIALOG && lparam != 0) {
        SetWindowLongA(dialog, DWL_USER, ((DialogInitParam *)lparam)->Param);
    }

    BOOL result = Standard_Dialog_Proc(dialog, message, wparam, lparam);
    if (result) return result;

    FactionSelectDialogControl * control = (FactionSelectDialogControl *)GetWindowLongA(dialog, DWL_USER);

    switch (message) {
        case WM_NCHITTEST:
        {
            POINT point;
            point.x = LOWORD(lparam);
            point.y = HIWORD(lparam);
            control->Mouse_Over(dialog, point);
            return FALSE;
        }

        case WM_DRAWITEM:
            Func_5F6060(lparam);
            return TRUE;

        case WM_PAINT:
            Func_5F6B50(dialog);
            control->Draw(dialog);
            Func_5DE390(dialog);
            ValidateRect(dialog, NULL);
            return TRUE;

        case WM_ERASEBKGND:
            return TRUE;

        case WM_COMMAND:
            if (LOWORD(wparam) == 0x686) {
                control->End(dialog, -1);
                return FALSE;
            }
            break;

        case WM_LBUTTONUP:
            if (control->Side != 0) {
                control->End(dialog, 1);
            }
            break;

        case 0x497:
            return FALSE;

        case 0x4e9:
            if (*(HWND *)lparam == dialog) {
                wchar_t const * text;
                switch (control->Side) {
                    case 2:
#line 176 "C:\\RA2\\WorldDom.cpp"
                        text = Fetch_String("WDT:FactionSelectAlliesToolTip", NULL, __FILE__, __LINE__);
                        break;
                    case 3:
#line 179
                        text = Fetch_String("WDT:FactionSelectSovietToolTip", NULL, __FILE__, __LINE__);
                        break;
                    default:
#line 182
                        text = Fetch_String("WDT:FactionSelectToolTip", NULL, __FILE__, __LINE__);
                        break;
                }
                *(WideStringClass *)(lparam + 8) = text;
                return FALSE;
            }
            break;
    }
    return FALSE;
}
