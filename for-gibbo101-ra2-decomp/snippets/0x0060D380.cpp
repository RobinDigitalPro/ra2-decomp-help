// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0060D380 (175 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1e2e40 (VA 0x005E2E40, 176 bytes incl. padding)
// RA2 symbol : ?Dialog_Box@@YIHHP6GHPAUHWND__@@IIJ@Z_N@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9915)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __fastcall Dialog_Box(int resource, int (__stdcall *proc)(struct HWND__ *, unsigned int, unsigned int, long), bool Show) // RA2: as above
{
    HWND dialog = OwnerDraw::Begin_Dialog(resource, proc, 0); // RA2: as above
    int result = 0; // RA2: as above
    if (dialog) { // RA2: as above
        SetWindowLongA(dialog, DWL_USER, (LONG)&result); // RA2: as above
        OwnerDraw::Display_Dialog(dialog); // RA2: as above
        if (Show) { // RA2: as above
            Show_Dialog_With_Flag(dialog); // RA2: as above
        }
        while (result == 0) { // RA2: as above
            if (OwnerDraw::Dialog_Message_Handler()) { // RA2: as above
                break;
            }
        }
        OwnerDraw::End_Dialog(dialog); // RA2: as above
    }
    return result; // RA2: as above
}
