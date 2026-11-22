// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00709800 (27 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2c9c20 (VA 0x006C9C20, 32 bytes incl. padding)
// RA2 symbol : ?Is_Not_Guard_Or_Sticky@TechnoClass@@QAEHW4MissionType@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7826)
// source TU  : src/m85/src/techno.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Whether the mission is neither guard nor sticky.
/// </summary>
int TechnoClass::Is_Not_Guard_Or_Sticky(MissionType mission) // RA2: not in TibSun, at 0x6D46B0
{
	if (mission != MISSION_GUARD && mission != MISSION_STICKY) {
		return(1);
	}
	return(0);
}
