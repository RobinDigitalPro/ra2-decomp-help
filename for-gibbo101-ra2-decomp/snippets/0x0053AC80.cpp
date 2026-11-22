// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0053AC80 (119 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x11ffc0 (VA 0x0051FFC0, 128 bytes incl. padding)
// RA2 symbol : ?Adjust_Scheme_Set_Tints@@YIXHHH_N@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9126)
// source TU  : src/ra2/Ion.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x11ffc0
void Adjust_Scheme_Set_Tints(int red, int green, int blue, bool flag)
{
    SchemeSetIterator iter;
    DynamicVectorClass<ColorScheme *> * schemes = iter.Next();
    while (schemes) {
        int count = Scheme_Set_Count();
        for (int index = 0; index < count; index++) {
            (*schemes)[index]->Convert->Adjust_Tint(red, green, blue, flag);
        }
        schemes = iter.Next();
    }
}
