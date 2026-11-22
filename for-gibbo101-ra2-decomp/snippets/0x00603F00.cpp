// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00603F00 (84 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1da610 (VA 0x005DA610, 96 bytes incl. padding)
// RA2 symbol : ?Get_Item_Tip_Text@OwnerDraw@@YI?AVWideWstring@@PAUHWND__@@HH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8235)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

WideWstring __fastcall Get_Item_Tip_Text(HWND window, int a, int b) // RA2: as above
{
    TextRequest request; // RA2: as above
    request.Item = a; // RA2: as above
    request.Index = b; // RA2: as above
    SendMessageA(window, 0x4e9, 0, (LPARAM)&request); // RA2: as above
    return request.Text; // RA2: as above
}
