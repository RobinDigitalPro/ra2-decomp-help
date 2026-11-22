// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00623840 (54 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1f8490 (VA 0x005F8490, 64 bytes incl. padding)
// RA2 symbol : ?Clear_ComboBox@@YIHPAUHWND__@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8485)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __fastcall Clear_ComboBox(HWND combo) // RA2: as above
{
    int index = SendMessageA(combo, 0x146, 0, 0); // RA2: as above
    while (index--) { // RA2: as above
        SendMessageA(combo, 0x144, index, 0); // RA2: as above
    }
    return 0; // RA2: as above
}
