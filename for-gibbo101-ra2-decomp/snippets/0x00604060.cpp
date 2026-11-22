// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00604060 (71 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1da710 (VA 0x005DA710, 80 bytes incl. padding)
// RA2 symbol : ?Control_Tooltip@OwnerDraw@@YI?AVWideWstring@@IPAUHWND__@@@Z
// similarity : 0.9600 (very-similar, masked instruction tokens; shape 0.8475)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

WideWstring __fastcall Control_Tooltip(unsigned int key, HWND window) // RA2: as above
{
    char const *label = Control_Tooltip_Label(key, window); // RA2: as above
    if (label) { // RA2: as above
        return WideWstring(StringTable::LoadString(label, 0, "C:\\RA2\\ownrdraw.cpp", 1863)); // RA2: as above; level-2 1.001: line 0x747
    }
    return WideWstring(L""); // RA2: as above
}
