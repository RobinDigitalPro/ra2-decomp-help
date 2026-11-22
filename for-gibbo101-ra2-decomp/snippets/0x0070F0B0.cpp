// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0070F0B0 (46 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2ce4d0 (VA 0x006CE4D0, 48 bytes incl. padding)
// RA2 symbol : ?Attack_Move_Action@@YI?AW4ActionType@@W41@HH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9474)
// source TU  : src/m85/src/techno.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Turns a plain move or attack order into the attack-move order while the force key is held.
/// </summary>
/// <param name="action">The action the cursor offers.</param>
/// <returns>The attack-move action for a move or an attack under the force key, else the action itself.</returns>
ActionType __fastcall Attack_Move_Action(ActionType action, int, int) // RA2: 0x6D8F60, a fastcall with one unused register and one unused stack argument (called at 0x49B5B5 in DisplayClass::Mouse_Left_Up)
{
	bool force = Can_Force_Order(); // RA2: the force key is asked first
	if (action == ACTION_MOVE) { // RA2: action 1 becomes 62
		if (force) { // RA2: as above
			return(ACTION_ATTACK_MOVE_NAV); // RA2: as above
		}
	} else if (action == ACTION_ATTACK && force) { // RA2: action 5 becomes 63
		return(ACTION_ATTACK_MOVE_TAR); // RA2: as above
	}
	return(action); // RA2: as above
}
