// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00709500 (74 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2c9920 (VA 0x006C9920, 80 bytes incl. padding)
// RA2 symbol : ?Is_Passive_Mission@TechnoClass@@QBEHXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9062)
// source TU  : src/m85/src/techno.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Whether the object is on a mission that keeps it from looking for targets.
/// </summary>
int TechnoClass::Is_Passive_Mission(void) const // RA2: not in TibSun, at 0x6D43B0
{
	MissionType mission = CurrentMission;
	if (mission != MISSION_SLEEP && mission != MISSION_ENTER && mission != MISSION_STOP && mission != MISSION_AMBUSH
		&& mission != MISSION_UNLOAD && mission != MISSION_CONSTRUCTION && mission != MISSION_DECONSTRUCTION
		&& mission != MISSION_REPAIR && mission != MISSION_MISSILE && mission != MISSION_HARMLESS && mission != MISSION_WAIT
		&& mission != MISSION_OPEN) {
		return(0);
	}
	return(1);
}
