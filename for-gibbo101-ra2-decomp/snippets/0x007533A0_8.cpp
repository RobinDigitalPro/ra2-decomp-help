// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007533A0 (3 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1b4d00 (VA 0x005B4D00, 16 bytes incl. padding)
// RA2 symbol : ?Reveal_Map@MultiplayerGameMode@@UAE_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.2353)
// source TU  : src/ra2/Multiplayer.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool MultiplayerGameMode::Reveal_Map()
{
    return true;
}
