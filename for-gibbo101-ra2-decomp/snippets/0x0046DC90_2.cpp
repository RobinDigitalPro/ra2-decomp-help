// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0046DC90 (40 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1a79f0 (VA 0x005A79F0, 48 bytes incl. padding)
// RA2 symbol : ?Score_Compare@@YAHPBX0@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8182)
// source TU  : src/ra2/MPScore.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x5a79f0: highest score first.
int __cdecl Score_Compare(void const * a, void const * b)
{
    MPScoreRecord * record1 = *(MPScoreRecord **)a;
    MPScoreRecord * record2 = *(MPScoreRecord **)b;
    if (record1->Score == record2->Score) return 0;
    return (record1->Score > record2->Score) ? -1 : 1;
}
