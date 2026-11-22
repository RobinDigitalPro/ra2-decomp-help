// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00732CC0 (58 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2ec4b0 (VA 0x006EC4B0, 64 bytes incl. padding)
// RA2 symbol : ?Type_Select_Key_Up@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8421)
// source TU  : src/ra2/UICmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x2ec4b0
void Type_Select_Key_Up()
{
    if (TypeSelectDown) {
        TypeSelectDown = false;
        if (abs((int)(timeGetTime() - TypeSelectTime)) <= 500) {
            Type_Select_Command();
            Map.Flag_To_Redraw(true);
        }
    }
}
