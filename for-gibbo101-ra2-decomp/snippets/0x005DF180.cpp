// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005DF180 (648 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1baae0 (VA 0x005BAAE0, 656 bytes incl. padding)
// RA2 symbol : ?Options_Dialog_Proc@@YGHPAUHWND__@@IIJ@Z
// similarity : 0.9791 (very-similar, masked instruction tokens; shape 0.9795)
// source TU  : src/ra2/netdlg2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x5baae0
BOOL CALLBACK Options_Dialog_Proc(HWND dialog, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (!OptionsLocked) {
        switch (message) {
            case 0x497:
                Options_Func_5BE090(dialog, 1);
                return FALSE;

            case WM_HSCROLL:
                if (GetDlgItem(dialog, 0x529) == (HWND)lparam) {
                    Session.GameSpeed = 6 - SendDlgItemMessageA(dialog, 0x529, TBM_GETPOS, 0, 0);
                }
                if (GetDlgItem(dialog, 0x402) == (HWND)lparam) {
                    Session.Credits = SendDlgItemMessageA(dialog, 0x402, TBM_GETPOS, 0, 0);
                }
                if (GetDlgItem(dialog, 0x54f) == (HWND)lparam) {
                    Session.UnitCount = SendDlgItemMessageA(dialog, 0x54f, TBM_GETPOS, 0, 0);
                }
                return FALSE;

            case WM_COMMAND:
                switch (LOWORD(wparam)) {
                    case 0x54e:
                        Session.ShortGame = false;
                        if (SendDlgItemMessageA(dialog, 0x54e, BM_GETCHECK, 0, 0) == 1) {
                            Session.ShortGame = true;
                            if (!Session.Bases) {
                                Session.Bases = true;
                                SendDlgItemMessageA(dialog, 0x54b, BM_SETCHECK, 1, 0);
                            }
                        }
                        return FALSE;

                    case 0x54d:
                        Session.Crates = false;
                        if (SendDlgItemMessageA(dialog, 0x54d, BM_GETCHECK, 0, 0) == 1) {
                            Session.Crates = true;
                        }
                        return FALSE;

                    case 0x3e8:
                        Session.MCVRedeploy = false;
                        if (SendDlgItemMessageA(dialog, 0x3e8, BM_GETCHECK, 0, 0) == 1) {
                            Session.MCVRedeploy = true;
                        }
                        return FALSE;

                    case 0x624:
                        Session.BridgeDestruction = false;
                        if (SendDlgItemMessageA(dialog, 0x624, BM_GETCHECK, 0, 0) == 1) {
                            Session.BridgeDestruction = true;
                        }
                        return FALSE;

                    case 0x69d:
                        Session.BuildOffAlly = false;
                        if (SendDlgItemMessageA(dialog, 0x69d, BM_GETCHECK, 0, 0) == 1) {
                            Session.BuildOffAlly = true;
                        }
                        return FALSE;

                    case 0x69a:
                        Session.SuperWeapons = false;
                        if (SendDlgItemMessageA(dialog, 0x69a, BM_GETCHECK, 0, 0) == 1) {
                            Session.SuperWeapons = true;
                        }
                        return FALSE;
                }
                break;
        }
    }
    return FALSE;
}
