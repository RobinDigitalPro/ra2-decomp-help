// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00471400 (32 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x67630 (VA 0x00467630, 32 bytes incl. padding)
// RA2 symbol : ?Sort_Scores@CampaignEndScoreClass@@SIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/ra2/CampScor.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x467630
void CampaignEndScoreClass::Sort_Scores()
{
    if (EndScoreCount > 1) {
        qsort(EndSortedScores, EndScoreCount, sizeof(EndSortedScores[0]), CampaignScoreClass::Score_Compare);
    }
}
