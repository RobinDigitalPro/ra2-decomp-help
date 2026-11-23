// ra2-decomp help snippet, update 2026-11-23 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00684370 (676 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0x253590 (VA 0x00653590, 657 bytes without padding)
// RA2 symbol : ?Wait_For_Players_To_Load@@YI_NXZ
// similarity : 0.8133 (partial, masked instruction tokens; shape 0.8235)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/scenario.cpp
// License    : GPL-3.0-or-later. Our source is GPL and contains EA GPL code (section 7 terms)
//              and code adapted from mischa85/RedAlert2 and gibbo101/ra2-decomp; their
//              credits are kept. The notice of the source file follows. See ../README.md.
// Use        : a read-only lead. RA2 layouts and names; port it and match it on your own checker.

/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2025 Electronic Arts Inc.
 * Copyright 2026 OpenTS contributors
 *
 * Contains material derived from Electronic Arts source code.
 * Modified by OpenTS contributors, 2026.
 * EA's GPLv3 Section 7 additional terms and supplemental warranty
 * disclaimers apply; see LICENSE.md.
 ******************************************************************************/

/// <summary>
/// Waits for the other players to finish loading the scenario.
/// The network is kept alive and the progress display updated until every machine reports
/// that it is ready. A player who stops making progress is dropped rather than being
/// allowed to hold the game up forever. Solo and skirmish games have nobody to wait for.
/// </summary>
/// <returns>bool; Did everyone make it into the game?</returns>
bool Wait_For_Players_To_Load(void)
{
	if (Session.Type == GAME_NORMAL || Session.Type == GAME_SKIRMISH) {
		return(true);
	}

	CDTimerClass<SystemTimerClass> wait_timeout;
	CDTimerClass<SystemTimerClass> timer = TIMER_SECOND * 5;

	wait_timeout = 60 * TIMER_SECOND;
	double last_progress = Progress.Get_Current_Progress();

	for (;;) {
		Keyboard->Check();
		Call_Back();

		if (Session.Type == GAME_MODEM && SerialPort) {
			int modemstatus = SerialPort->Get_Modem_Status();
			if ((modemstatus & WinModemClass::CD_SET) == 0) {
				DebugString("Carrier Detect is false. Aborting load wait\n");
				return(false);
			}
		}

		if (wait_timeout <= 0) {
			for (int i = 1, slot = 1; i < Session.Players.Count(); slot++, i++) { // RA2: slot and i step together except after a drop; level-2 1.001: slot steps first
				if (Progress.PlayerProgress[slot] / Progress.MainProgress < 0.999) { // RA2: below 0.999 instead of not exactly 1.0; level-2 1.001: the slot's ratio is computed in place
					DebugString("Player %s failed to make it into the game. Dropping %s\n", Session.Players[i]->Name, Session.Players[i]->Name); // level-2 1.001: the names are passed as they are (no Wide_To_Narrow)
					int id = Session.Players[i]->Player.ID; // RA2: the connection's id is kept for the master test
					Destroy_Connection(id, 1); // RA2: as above
					if (Session.Am_I_Master(Houses[id])) { // RA2: a dropped master is forgotten (0x66F150)
						Session.MasterPlayerID = -1; // RA2: as above
						memset(Session.MasterPlayerName, 0, sizeof(Session.MasterPlayerName)); // RA2: as above
					}
					i--;
				}
			}
			return(false);
		}

		double current_progress = Progress.Get_Current_Progress();
		if (current_progress >= 0.9995) {
			Session.Update_Progress(100 + (Scen->IsRandom ? 100 : 0));
			break;
		}

		if (current_progress != last_progress) {
			wait_timeout = 60 * TIMER_SECOND;
			last_progress = current_progress;
		}

		if (timer <= 0) {
			timer = TIMER_SECOND;
			Session.Update_Progress(100 + (Scen->IsRandom ? 100 : 0));
		}
	}
	return(true);
}
