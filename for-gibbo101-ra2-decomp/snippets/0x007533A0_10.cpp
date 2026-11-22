// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007533A0 (3 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x3558d0 (VA 0x007558D0, 16 bytes incl. padding)
// RA2 symbol : ?WDT_Available@@YI_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.2353)
// source TU  : src/ra2/WorldDom.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x3558d0 (no callers found)
bool WDT_Available()
{
    return true;
}
