// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0049BCE0 (338 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x8e4f0 (VA 0x0048E4F0, 352 bytes incl. padding)
// RA2 symbol : ?Get_Scores@CoopCampaignClass@@QAE_NAAV?$DynamicVectorClass@PAUMPScoreRecord@@@@PAH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9507)
// source TU  : src/ra2/coopcamp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x48e4f0: two new score lines with the campaign totals (local player first).
bool CoopCampaignClass::Get_Scores(DynamicVectorClass<MPScoreRecord *> & list, int * time)
{
    if (!IsActive) return false;

    while (list.Count() != 0) {
        delete list[0];
        list.Delete(0);
    }

    MPScoreRecord * score1 = new MPScoreRecord;
    Fill_Coop_Score(score1, false);
    MPScoreRecord * score2 = new MPScoreRecord;
    Fill_Coop_Score(score2, true);

    if (strcmp(Players[0].Name, To_Narrow(score1->Name)) != 0) {
        MPScoreRecord * temp = score1;
        score1 = score2;
        score2 = temp;
    }

    for (int index = 0; index < 2; index++) {
        MPScoreRecord * score = (index == 0) ? score1 : score2;
        score->Kills = Kills[index];
        score->Built = Built[index];
        score->Lost = Lost[index];
        score->Wins = CurrentMap;
        score->Score = Score[index];
        list.Add(score);
    }
    *time = Time;
    return true;
}
