// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0069B540 (30 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x268a80 (VA 0x00668A80, 32 bytes incl. padding)
// RA2 symbol : ?Reset_AI@GameOptionsType@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9091)
// source TU  : src/m85/src/session.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void GameOptionsType::Reset_AI(void) // RA2: RA2's signature
{
	AIPlayers = 0; // RA2: 0x00672810
	for (int index = 0; index < 8; index++) { // RA2: RA2's form of GameOptionsType::Reset_AI
		AISlots.Countries[index] = -1; // RA2: as above
		AISlots.Colors[index] = -1; // RA2: as above
	}
}
