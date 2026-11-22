// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006242B0 (427 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1f8f10 (VA 0x005F8F10, 432 bytes incl. padding)
// RA2 symbol : ?Control_Test@OwnerDraw@@YI_NPAUHWND__@@@Z
// similarity : 0.9883 (very-similar, masked instruction tokens; shape 0.9856)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Control_Test(HWND window) // RA2: as above
{
    char name[128]; // RA2: as above
    GetClassNameA(window,name,sizeof(name)); // RA2: as above
    if(!strcmp(name,"Edit"))return true; // RA2: as above
    if(!strcmp(name,"NewEdit"))return true; // RA2: as above
    if(!strcmp(name,"ListBox")) { // RA2: as above
        WinData *record=0; // RA2: as above
        unsigned int const &key=(unsigned int const &)window; // RA2: as above
        if(Control_Table.getPointer(key, &record))return record->SkipTests==1; // RA2: as above
    }
    if(!strcmp(name,"ComboBox"))return (GetWindowLongA(window,-16)&3)!=3; // RA2: as above
    return false; // RA2: as above
}
