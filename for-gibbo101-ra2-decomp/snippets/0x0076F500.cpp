// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0076F500 (94 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x325350 (VA 0x00725350, 96 bytes incl. padding)
// RA2 symbol : ?Create@State@WorldDominationTour@@SI?AV?$rc_ptr@VState@WorldDominationTour@@@@XZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9688)
// source TU  : src/ra2/unnamed/TU_7250F0.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x325350
rc_ptr<State> State::Create()
{
    return rc_ptr<State>(new State());
}
