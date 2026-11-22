// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00623DA0 (83 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1f89f0 (VA 0x005F89F0, 96 bytes incl. padding)
// RA2 symbol : ?Choice_Dialog_Proc@@YGHPAUHWND__@@IIJ@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8219)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __stdcall Choice_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) // RA2: as above
{
    int result = OwnerDraw::Default_Dialog_Proc(window, message, wparam, lparam); // RA2: as above
    if (result) { // RA2: as above
        return result; // RA2: as above
    }
    int *choice = (int *)GetWindowLongA(window, DWL_USER); // RA2: as above
    if (message == 0x111) { // RA2: as above
        int id = wparam & 0xffff; // RA2: as above
        if (id >= 0x5c0 && id <= 0x5c1) { // RA2: as above
            *choice = id;
        }
    }
    return 0; // RA2: as above
}
