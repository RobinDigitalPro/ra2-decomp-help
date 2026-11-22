// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00470D30 (1731 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x66f60 (VA 0x00466F60, 1744 bytes incl. padding)
// RA2 symbol : ?Dialog_Proc@CampaignEndScoreClass@@SGHPAUHWND__@@IIJ@Z
// similarity : 0.9804 (very-similar, masked instruction tokens; shape 0.9886)
// source TU  : src/ra2/CampScor.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x466f60. The cases leave with break (single return at the end); with per-case returns VC6
// saves ebp only inside the WM_INITDIALOG branch instead of right after the early return.
BOOL CALLBACK CampaignEndScoreClass::Dialog_Proc(HWND dialog, UINT message, WPARAM wparam, LPARAM lparam)
{
    BOOL result = Standard_Dialog_Proc(dialog, message, wparam, lparam);
    if (result) return result;

    int * retval = (int *)GetWindowLongA(dialog, DWL_USER);
    HWND item;

    switch (message) {
        case WM_INITDIALOG:
        {
            wchar_t buffer[32];
            buffer[0] = L'\0';

            item = GetDlgItem(dialog, IDC_CAMPAIGN_NAME);
            SendMessageA(item, WM_SET_TEXT_WIDE, 0, (LPARAM)EndName);
#line 710 "C:\\RA2\\CampScor.cpp"
            swprintf(buffer, Fetch_String("GUI:CampaignLabel", NULL, __FILE__, __LINE__), EndCampaignNumber);
            item = GetDlgItem(dialog, IDC_CAMPAIGN_LABEL);
            SendMessageA(item, WM_SET_TEXT_WIDE, 0, (LPARAM)buffer);
            if (EndDifficulty == 0) {
#line 714 "C:\\RA2\\CampScor.cpp"
                swprintf(buffer, Fetch_String("GUI:DifficultyString", NULL, __FILE__, __LINE__), Fetch_String("TXT_DIFFICULTY_EASY", NULL, __FILE__, __LINE__));
            } else if (EndDifficulty == 1) {
#line 716 "C:\\RA2\\CampScor.cpp"
                swprintf(buffer, Fetch_String("GUI:DifficultyString", NULL, __FILE__, __LINE__), Fetch_String("TXT_DIFFICULTY_MEDIUM", NULL, __FILE__, __LINE__));
            } else if (EndDifficulty == 2) {
#line 718 "C:\\RA2\\CampScor.cpp"
                swprintf(buffer, Fetch_String("GUI:DifficultyString", NULL, __FILE__, __LINE__), Fetch_String("TXT_DIFFICULTY_BRUTAL", NULL, __FILE__, __LINE__));
            } else {
#line 720 "C:\\RA2\\CampScor.cpp"
                swprintf(buffer, Fetch_String("GUI:Blank", NULL, __FILE__, __LINE__));
            }
            item = GetDlgItem(dialog, IDC_CAMPAIGN_DIFFICULTY);
            SendMessageA(item, WM_SET_TEXT_WIDE, 0, (LPARAM)buffer);
            Format_Time(buffer, EndTime / 60);
            item = GetDlgItem(dialog, IDC_CAMPAIGN_TIME);
            SendMessageA(item, WM_SET_TEXT_WIDE, 0, (LPARAM)buffer);

            for (int index = 0; index < EndScoreCount; index++) {
                ColorSchemeClass * scheme = ColorSchemes[EndSortedScores[index]->Scheme];
                RGBClass rgb = scheme->BaseColor.To_RGB();
                COLORREF color = RGB(rgb.Red, rgb.Green, rgb.Blue);

                int id = CampaignControls[index][0];
                wchar_t const * name = EndSortedScores[index]->Name;
                item = GetDlgItem(dialog, id);
                SendMessageA(item, WM_SET_TEXT_WIDE, 0, (LPARAM)name);
                item = GetDlgItem(dialog, id);
                SendMessageA(item, WM_SET_COLOR, 0, color);

                id = CampaignControls[index][1];
                Set_Dialog_Number(dialog, id, EndSortedScores[index]->Kills);
                item = GetDlgItem(dialog, id);
                SendMessageA(item, WM_SET_COLOR, 0, color);

                id = CampaignControls[index][2];
                Set_Dialog_Number(dialog, id, EndSortedScores[index]->Lost);
                item = GetDlgItem(dialog, id);
                SendMessageA(item, WM_SET_COLOR, 0, color);

                id = CampaignControls[index][3];
                Set_Dialog_Number(dialog, id, EndSortedScores[index]->Built);
                item = GetDlgItem(dialog, id);
                SendMessageA(item, WM_SET_COLOR, 0, color);

                id = CampaignControls[index][4];
                Set_Dialog_Number(dialog, id, EndSortedScores[index]->Score);
                item = GetDlgItem(dialog, id);
                SendMessageA(item, WM_SET_COLOR, 0, color);

                if (index == 0) {
                    name = EndSortedScores[index]->Name;
                    item = GetDlgItem(dialog, IDC_END_FIRST_NAME);
                    SendMessageA(item, WM_SET_TEXT_WIDE, 0, (LPARAM)name);
                    item = GetDlgItem(dialog, IDC_END_FIRST_NAME);
                    SendMessageA(item, WM_SET_COLOR, 0, color);
                    swprintf(buffer, L"%d", EndSortedScores[index]->Score);
                    item = GetDlgItem(dialog, IDC_END_FIRST_SCORE);
                    SendMessageA(item, WM_SET_TEXT_WIDE, 0, (LPARAM)buffer);
                    item = GetDlgItem(dialog, IDC_END_FIRST_SCORE);
                    SendMessageA(item, WM_SET_COLOR, 0, color);
                } else if (index == 1) {
                    name = EndSortedScores[index]->Name;
                    item = GetDlgItem(dialog, IDC_END_SECOND_NAME);
                    SendMessageA(item, WM_SET_TEXT_WIDE, 0, (LPARAM)name);
                    item = GetDlgItem(dialog, IDC_END_SECOND_NAME);
                    SendMessageA(item, WM_SET_COLOR, 0, color);
                    swprintf(buffer, L"%d", EndSortedScores[index]->Score);
                    item = GetDlgItem(dialog, IDC_END_SECOND_SCORE);
                    SendMessageA(item, WM_SET_TEXT_WIDE, 0, (LPARAM)buffer);
                    item = GetDlgItem(dialog, IDC_END_SECOND_SCORE);
                    SendMessageA(item, WM_SET_COLOR, 0, color);
                }
            }
            break;
        }

        case WM_COMMAND:
            if (LOWORD(wparam) == IDC_CAMPAIGN_OK) {
                *retval = 1;
                break;
            }
            break;

        case WM_PAINT:
            Func_5F6B50(dialog);
            Func_5DE390(dialog);
            break;

        case WM_DIALOG_INIT:
            item = GetDlgItem(dialog, IDC_END_MOVIE);
            PostMessageA(item, WM_USER + 0xD7, 0, (LPARAM)dialog);
            break;

        case WM_USER + 0xD8:
            if (wparam == 0) {
                SendDlgItemMessageA(dialog, IDC_END_MOVIE, WM_USER + 0xD5, 0, 0x1d);
            }
            break;

        case WM_USER + 0xEC:
            SendDlgItemMessageA(dialog, IDC_END_MOVIE, WM_USER + 0xD3, 0, 0);
            break;

        case WM_CAMPAIGN_HIDE:
            Func_514F50(0, true);
            ShowWindow(dialog, SW_HIDE);
            Func_5E5050(dialog, 1);
            break;
    }
    return FALSE;
}
