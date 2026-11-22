// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007533A0 (3 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1b3e80 (VA 0x005B3E80, 16 bytes incl. padding)
// RA2 symbol : ?Virtual_20@MultiplayerGameMode@@UAE_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.2353)
// source TU  : src/ra2/Multiplayer.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool MultiplayerGameMode::Virtual_20()
{
    return true;
}
