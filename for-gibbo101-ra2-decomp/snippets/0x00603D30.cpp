// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00603D30 (116 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1da440 (VA 0x005DA440, 128 bytes incl. padding)
// RA2 symbol : ?Set_Control_Image@OwnerDraw@@YIXPAUHWND__@@PAVSurface@@@Z
// similarity : 0.9556 (very-similar, masked instruction tokens; shape 0.8824)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Set_Control_Image(HWND control, Surface *image) // RA2: as above
{
    WinData *record = 0; // RA2: as above
    Control_Table.getPointer((unsigned int)control, &record); // RA2: as above
    if (record) { // RA2: as above
        record->PictureMode = 2; // RA2: as above
        record->Image = image; // RA2: as above
        InvalidateRect(control, 0, TRUE); // RA2: as above
    }
}
