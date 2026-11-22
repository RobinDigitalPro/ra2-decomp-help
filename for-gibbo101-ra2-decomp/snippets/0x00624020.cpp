// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00624020 (95 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1f8c70 (VA 0x005F8C70, 96 bytes incl. padding)
// RA2 symbol : ?Get_Combo_Item_Wide_Text@@YIJPAUHWND__@@IAAVWideWstring@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9877)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

LRESULT __fastcall Get_Combo_Item_Wide_Text(HWND window, WPARAM index, WideWstring &text) // RA2: as above
{
    LRESULT length = SendMessageA(window, 0x149, index, 0); // RA2: as above
    if (length <= 0) { // RA2: as above
        text.clear(); // RA2: as above
    }
    unsigned short *buffer = new unsigned short[length + 2]; // RA2: as above
    LRESULT result = SendMessageA(window, 0x4C3, index, (LPARAM)buffer); // RA2: as above
    text = buffer; // RA2: as above
    delete [] buffer; // RA2: as above
    return result; // RA2: as above
}
