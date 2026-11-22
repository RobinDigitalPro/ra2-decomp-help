// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005D6750 (49 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1b4280 (VA 0x005B4280, 64 bytes incl. padding)
// RA2 symbol : ?Clear_Teams@MultiplayerGameMode@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7619)
// source TU  : src/ra2/Multiplayer.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void MultiplayerGameMode::Clear_Teams()
{
    for (int index = 0; index < Teams.Count(); index++) {
        delete Teams[index];
    }
    Teams.Clear();
}
