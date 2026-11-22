// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007094E0 (30 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2c9900 (VA 0x006C9900, 32 bytes incl. padding)
// RA2 symbol : ?Is_Moving_Guarding_Or_Harvesting@TechnoClass@@QBEHXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9167)
// source TU  : src/m85/src/techno.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Whether the object is moving, guarding or harvesting.
/// </summary>
int TechnoClass::Is_Moving_Guarding_Or_Harvesting(void) const // RA2: not in TibSun, at 0x6D4390
{
	MissionType mission = CurrentMission;
	if (mission != MISSION_MOVE && mission != MISSION_HARVEST && mission != MISSION_GUARD) {
		return(0);
	}
	return(1);
}
