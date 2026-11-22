// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00439030 (70 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x364b0 (VA 0x004364B0, 80 bytes incl. padding)
// RA2 symbol : ?Add_Bomb@BombListClass@@QAEXPAVBombClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8571)
// source TU  : src/m85/src/bomb.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Puts a bomb into the list of planted bombs.
/// </summary>
/// <param name="bomb">The bomb to add.</param>
void BombListClass::Add_Bomb(BombClass * bomb) // RA2: 0x00436630
{
	Planted.Add(bomb); // RA2: as above
}
