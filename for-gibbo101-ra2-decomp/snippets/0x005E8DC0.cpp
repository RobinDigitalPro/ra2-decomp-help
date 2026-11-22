// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E8DC0 (214 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c2b20 (VA 0x005C2B20, 208 bytes incl. padding)
// RA2 symbol : ?Build_Player_Text@@YIXPAG@Z
// similarity : 0.9672 (very-similar, masked instruction tokens; shape 0.9677)
// source TU  : src/ra2/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x5c2b20
void Build_Player_Text(wchar_t * buffer)
{
    buffer[0] = 0;
    for (int i = 0; i < 8; i++) {
        MPPlayerNode * node = Session.Slots[i];
        WideStringClass name;
        if (Is_Real_Player(node)) {
            name = node->Name;
        } else {
            CharStringClass tag = Slot_Tag(node);
            name = To_WideString(tag);
        }
        wcscat(buffer, (WideStringClass const &)name);  // level-2 1.001: the const conversion (0x75bd30) is called
        wcscat(buffer, L",");
    }
}
