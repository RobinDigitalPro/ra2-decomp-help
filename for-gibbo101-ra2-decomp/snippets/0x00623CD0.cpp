// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00623CD0 (205 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1f8920 (VA 0x005F8920, 208 bytes incl. padding)
// RA2 symbol : ?Prompt_Dialog@@YI_NPBG@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9778)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Prompt_Dialog(unsigned short const *text) // RA2: as above
{
    int result = -1; // RA2: as above
    HWND dialog = OwnerDraw::Begin_Dialog(0x10d, Choice_Dialog_Proc, 0); // RA2: as above
    if (dialog) { // RA2: as above
        HWND item = GetDlgItem(dialog, 0x5b0); // RA2: as above
        SendMessageA(item, 0x4b2, 0, (LPARAM)text); // RA2: as above
        SetWindowLongA(dialog, DWL_USER, (LONG)&result); // RA2: as above
        OwnerDraw::Display_Dialog(dialog); // RA2: as above
        while (result < 0) { // RA2: as above
            Windows_Message_Handler();
            if (Session.Type != GAME_NORMAL && Session.Type != GAME_SKIRMISH && !Session_Busy && // RA2: as above
                Session.Suspended == 0 && !Is_In_Main_Loop() && Main_Loop()) { // RA2: as above
                break;
            }
        }
        OwnerDraw::End_Dialog(dialog); // RA2: as above
    }
    return result == 0x5c1; // RA2: as above
}
