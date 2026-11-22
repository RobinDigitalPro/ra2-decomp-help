// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005D6620 (106 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1b4150 (VA 0x005B4150, 112 bytes incl. padding)
// RA2 symbol : ?Find_Team@MultiplayerGameMode@@QAEPAVMultiplayerTeam@@H@Z
// similarity : 0.9787 (very-similar, masked instruction tokens; shape 0.9400)
// source TU  : src/ra2/Multiplayer.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

MultiplayerTeam * MultiplayerGameMode::Find_Team(int id)
{
    if (Teams.ActiveCount < 3) {
        Clear_Teams();
        Create_Teams(Teams);
    }
    for (int index = 0; index < Teams.ActiveCount; index++) {
        MultiplayerTeam * team = Teams[index];
        if (team && team->ID == id) {
            return team;
        }
    }
    return NULL;
}
