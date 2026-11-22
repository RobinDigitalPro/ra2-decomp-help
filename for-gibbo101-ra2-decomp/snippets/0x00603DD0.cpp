// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00603DD0 (22 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1da4e0 (VA 0x005DA4E0, 32 bytes incl. padding)
// RA2 symbol : ?Send_Control_Flag@@YIXPAUHWND__@@E@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5833)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Send_Control_Flag(HWND window, unsigned char flag) // RA2: as above
{
    SendMessageA(window, 0x4e6, 0, (int)(flag & 0xff)); // RA2: as above
}
