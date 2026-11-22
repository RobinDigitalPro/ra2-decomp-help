// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00796B20 (1 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x33f870 (VA 0x0073F870, 16 bytes incl. padding)
// RA2 symbol : ?Wonline_Stub_73F870@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.1176)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Wonline_Stub_73F870(void) // level-2 1.001: 0x0073F870 (YR 0x00796B20), an empty function between Poke_The_Host and Ask_Locale; no caller, real name unknown
{
}
