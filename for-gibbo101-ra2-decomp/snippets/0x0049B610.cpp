// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0049B610 (72 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x8de20 (VA 0x0048DE20, 80 bytes incl. padding)
// RA2 symbol : ??0CoopCampaignClass@@QAE@XZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8621)
// source TU  : src/ra2/coopcamp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x48de20
CoopCampaignClass::CoopCampaignClass()
{
    Players[0].Name[0] = '\0';
    Players[1].Name[0] = '\0';
    Players[0].House = -2;
    Players[1].House = -2;
    Players[0].Color = -2;
    Players[1].Color = -2;
    Maps = NULL;
    CampaignType = -1;
    IsActive = false;
    MapCount = 0;
    CurrentMap = -1;
    Kills[0] = 0;
    Kills[1] = 0;
    Built[0] = 0;
    Built[1] = 0;
    Lost[0] = 0;
    Lost[1] = 0;
    Time = 0;
    Score[0] = 0;
    Score[1] = 0;
}
