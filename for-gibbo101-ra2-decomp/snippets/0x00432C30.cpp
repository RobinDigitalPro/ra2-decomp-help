// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00432C30 (23 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x30300 (VA 0x00430300, 32 bytes incl. padding)
// RA2 symbol : ?Pause@BinkMovieClass@@QAEX_N@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6087)
// source TU  : src/ra2/unnamed/TU_42FD50.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x430300
void BinkMovieClass::Pause(bool pause)
{
    BinkPause(Bink, pause);
}
