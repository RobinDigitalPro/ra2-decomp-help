// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005BCC20 (1 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x19b010 (VA 0x0059B010, 16 bytes incl. padding)
// RA2 symbol : ??1MonoClass@@QAE@XZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.1176)
// source TU  : src/m85/src/mono.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

MonoClass::~MonoClass(void) // RA2: 0x0059E220, an empty destructor
{
}
