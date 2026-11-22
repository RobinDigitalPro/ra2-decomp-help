// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00432A60 (80 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2fde0 (VA 0x0042FDE0, 80 bytes incl. padding)
// RA2 symbol : ??1BinkMovieClass@@QAE@XZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/ra2/unnamed/TU_42FD50.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x42fde0
BinkMovieClass::~BinkMovieClass()
{
    Close();
}
