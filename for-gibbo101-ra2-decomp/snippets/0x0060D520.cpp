// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0060D520 (29 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1e2fe0 (VA 0x005E2FE0, 32 bytes incl. padding)
// RA2 symbol : ?New_Edit_Window_Proc@OwnerDraw@@YGJPAUHWND__@@IIJ@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8696)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

LRESULT __stdcall OwnerDraw::New_Edit_Window_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) // RA2: as above
{
    return DefWindowProcA(window, message, wparam, lparam); // RA2: as above
}
