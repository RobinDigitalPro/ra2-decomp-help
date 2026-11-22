// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0060A300 (39 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1e0240 (VA 0x005E0240, 48 bytes incl. padding)
// RA2 symbol : ?Has_Visible_Default_Button@OwnerDraw@@YI_NPAUHWND__@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6897)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Has_Visible_Default_Button(HWND dialog) // RA2: as above
{
    Visible_Default_Buttons = 0; // RA2: as above
    EnumChildWindows(dialog, Count_Visible_Default_Buttons, 0); // RA2: as above
    return Visible_Default_Buttons >= 1; // RA2: as above
}
