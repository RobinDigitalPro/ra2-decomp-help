// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00730970 (27 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2ea7d0 (VA 0x006EA7D0, 32 bytes incl. padding)
// RA2 symbol : ?Clear_Cycle_List@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7619)
// source TU  : src/ra2/UICmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x2ea7d0
void Clear_Cycle_List()
{
    if (CycleList) {
        delete CycleList;
        CycleList = 0;
    }
}
