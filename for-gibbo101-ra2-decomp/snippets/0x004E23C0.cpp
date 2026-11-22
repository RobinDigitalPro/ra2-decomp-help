// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004E23C0 (115 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xcfb50 (VA 0x004CFB50, 128 bytes incl. padding)
// RA2 symbol : ?Game_Controls_Command@@YIXPAUHWND__@@H0I@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8267)
// source TU  : src/ra2/GameDlg.CPP (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Game_Controls_Command(HWND dialog, int id, HWND control, UINT code)
{
    int * result = (int *)GetWindowLongA(dialog, DWL_USER);

    switch (id) {
        case IDC_BUTTON_52C:
            if (code == BN_CLICKED && Flag_A285A8 == true) {
                ExitMode_A28988 = 4;
                *result = 1;
            }
            break;

        case IDC_BUTTON_52D:
            if (code == BN_CLICKED && Flag_A285A8 == true) {
                ExitMode_A28988 = 6;
                *result = 1;
            }
            break;

        case IDC_OK:
            *result = 1;
            break;
    }
}
