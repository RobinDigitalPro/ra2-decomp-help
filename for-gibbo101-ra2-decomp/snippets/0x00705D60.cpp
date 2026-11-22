// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00705D60 (5 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2c69e0 (VA 0x006C69E0, 16 bytes incl. padding)
// RA2 symbol : ?Next_Planning_Node@TechnoClass@@QAE_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.1538)
// source TU  : src/m85/src/techno.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Moves on to the next node of this object's planning token.
/// </summary>
bool TechnoClass::Next_Planning_Node(void) // RA2: not in TibSun, at 0x6D1470
{
	return(TryNextPlanningTokenNode());
}
