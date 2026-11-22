// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0053AD00 (246 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x120040 (VA 0x00520040, 240 bytes incl. padding)
// RA2 symbol : ?Adjust_Tints@@YIXHHH_N@Z
// similarity : 0.9829 (very-similar, masked instruction tokens; shape 0.9503)
// source TU  : src/ra2/Ion.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x120040
void Adjust_Tints(int red, int green, int blue, bool flag)
{
    int index;
    for (index = 0; index < Converts.Count(); index++) {
        Converts[index]->Adjust_Tint(red, green, blue, flag);
    }
    for (index = 0; index < ColorSchemes.Count(); index++) {
        if (ColorSchemes[index]->Field310 > 1) {
            ColorSchemes[index]->Convert->Adjust_Tint(red, green, blue, flag);
        }
    }
    Adjust_Scheme_Set_Tints(red, green, blue, flag);
    Map.Func_49E310();
}
