// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0049B930 (835 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x8e140 (VA 0x0048E140, 848 bytes incl. padding)
// RA2 symbol : ?Next_Map@CoopCampaignClass@@QAE_NXZ
// similarity : 0.9778 (very-similar, masked instruction tokens; shape 0.9765)
// source TU  : src/ra2/coopcamp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x48e140: add the scores of the finished map.
bool CoopCampaignClass::Next_Map()
{
    if (!IsActive) return false;

    Debug_Printf("@@@@ NextMap\n");
    MPScoreRecord score1;
    MPScoreRecord score2;
    Fill_Coop_Score(&score1, false);
    Fill_Coop_Score(&score2, true);

    if (strcmp(Players[0].Name, To_Narrow(score1.Name)) == 0) {
        Debug_Printf("@@@@ %s is local\n", To_Narrow(score1.Name));
        Kills[0] += score1.Kills;
        Kills[1] += score2.Kills;
        Built[0] += score1.Built;
        Built[1] += score2.Built;
        Lost[0] += score1.Lost;
        Lost[1] += score2.Lost;
        Score[0] += score1.Score;
        Score[1] += score2.Score;
    } else {
        Debug_Printf("@@@@ Assuming %s is local\n", To_Narrow(score2.Name));
        Kills[1] += score1.Kills;
        Kills[0] += score2.Kills;
        Built[1] += score1.Built;
        Built[0] += score2.Built;
        Lost[1] += score1.Lost;
        Lost[0] += score2.Lost;
        Score[1] += score1.Score;
        Score[0] += score2.Score;
    }

    char gametime[256];
    char totaltime[256];
    Format_Time(gametime, Scen->ElapsedTimer.Value() / 60);
    Time += Scen->ElapsedTimer.Value();
    Format_Time(totaltime, Time);
    Debug_Printf("@@@@ Game Time: %s, Total Time: %s\n", gametime, totaltime);
    CurrentMap++;
    return true;
}
