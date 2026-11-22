// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00731CD0 (15 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2eb5b0 (VA 0x006EB5B0, 16 bytes incl. padding)
// RA2 symbol : ?Attack_Move_Mouse@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9091)
// source TU  : src/ra2/UICmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x2eb5b0
void Attack_Move_Mouse()
{
    Map.Func_59BF60(0x4D, false);
}
