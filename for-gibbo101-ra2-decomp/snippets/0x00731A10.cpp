// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00731A10 (31 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2eb300 (VA 0x006EB300, 32 bytes incl. padding)
// RA2 symbol : ?Delete_Command@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9524)
// source TU  : src/ra2/UICmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x2eb300 (Delete)
void Delete_Command()
{
    PlanningNodeClass * node = Selected_Planning_Node();
    if (node) {
        node->Delete();
    } else {
        Object836C18.Func_42E940(-1, -1);
    }
}
