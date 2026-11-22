// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00603DF0 (22 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1da500 (VA 0x005DA500, 32 bytes incl. padding)
// RA2 symbol : ?Is_Control_Checked@OwnerDraw@@YI_NPAUHWND__@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6154)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Is_Control_Checked(HWND window) // RA2: as above
{
    return SendMessageA(window, 0x4e7, 0, 0) ? true : false; // RA2: as above
}
