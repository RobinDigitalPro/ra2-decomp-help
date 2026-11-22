// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00603FC0 (152 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1da670 (VA 0x005DA670, 160 bytes incl. padding)
// RA2 symbol : ?Get_Item_Tip_Text_At@OwnerDraw@@YI?AVWideWstring@@PAUHWND__@@0HH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9273)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

WideWstring __fastcall Get_Item_Tip_Text_At(HWND window, HWND item, int x, int y) // RA2: as above
{
    int index = SendMessageA(item, 0x4e8, 0, (unsigned short)x | ((unsigned long)(unsigned short)y << 16)); // RA2: as above
    WideWstring text = Get_Item_Tip_Text(window, (int)item, index); // RA2: as above
    return text; // RA2: as above
}
