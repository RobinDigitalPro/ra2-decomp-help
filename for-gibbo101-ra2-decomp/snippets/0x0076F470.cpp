// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0076F470 (139 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x3252c0 (VA 0x007252C0, 144 bytes incl. padding)
// RA2 symbol : ?Create@State@WorldDominationTour@@SI?AV?$rc_ptr@VState@WorldDominationTour@@@@ABV?$rc_ptr@VWDTState@@@@I@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9505)
// source TU  : src/ra2/unnamed/TU_7250F0.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x3252c0
rc_ptr<State> State::Create(rc_ptr<WDTState> const & state, unsigned stage)
{
    return rc_ptr<State>(new State(state, stage));
}
