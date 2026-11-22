// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0046DC50 (62 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x65b10 (VA 0x00465B10, 64 bytes incl. padding)
// RA2 symbol : ?Sort_Scores@CampaignScoreClass@@SIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9565)
// source TU  : src/ra2/CampScor.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x465b10
void CampaignScoreClass::Sort_Scores()
{
    int count = ScoreData.PlayerCount;
    for (int index = 0; index < count; index++) {
        CampaignSortedScores[index] = &ScoreData.Records[index];
    }
    if (count > 1) {
        qsort(CampaignSortedScores, count, sizeof(CampaignSortedScores[0]), Score_Compare);
    }
}
