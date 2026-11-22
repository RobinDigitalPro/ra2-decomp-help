// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0060A230 (30 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1e0180 (VA 0x005E0180, 32 bytes incl. padding)
// RA2 symbol : ?Count_Free_Buttons@@YIIPAUHWND__@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8750)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

unsigned int __fastcall Count_Free_Buttons(HWND window) // RA2: as above
{
    Visible_Free_Buttons = 0; // RA2: as above
    EnumChildWindows(window, Count_Visible_Free_Buttons, 0); // RA2: as above
    return Visible_Free_Buttons; // RA2: as above
}
