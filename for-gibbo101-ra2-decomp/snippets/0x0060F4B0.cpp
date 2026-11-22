// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0060F4B0 (678 bytes; gibbo status: attempted-partial 93.4%)
// RA2 RVA    : 0x1e4da0 (VA 0x005E4DA0, 688 bytes incl. padding)
// RA2 symbol : ?Subclass_Dialog@OwnerDraw@@YI_NPAUHWND__@@J@Z
// similarity : 0.9712 (very-similar, masked instruction tokens; shape 0.9765)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Subclass_Dialog(HWND window, LPARAM lparam) // RA2: as above
{
    Register_Window_Classes(); // RA2: as above
    Current_Dialog = window; // RA2: as above
    EnumChildWindows(window, Set_Paint_Disabled, 1); // RA2: as above
    Set_Paint_Disabled(window, 1); // RA2: as above
    EnumChildWindows(window, Replace_Edit, 1); // RA2: as above
    EnumChildWindows(window, Subclass_Control, lparam); // RA2: as above
    Subclass_Control(window, lparam); // RA2: as above
    EnumChildWindows(window, Set_Paint_Disabled, 0); // RA2: as above
    Set_Paint_Disabled(window, 0); // RA2: as above
    return true; // RA2: as above
}
