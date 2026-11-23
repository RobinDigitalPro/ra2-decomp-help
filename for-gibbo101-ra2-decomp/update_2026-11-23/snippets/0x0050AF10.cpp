// ra2-decomp help snippet, update 2026-11-23 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0050AF10 (699 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0xf4020 (VA 0x004F4020, 646 bytes without padding)
// RA2 symbol : ?Update_Present_Super_Weapons@HouseClass@@QAEXXZ
// similarity : 0.7157 (partial, masked instruction tokens; shape 0.8235)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/house.cpp
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
/// Updates the availability of this house's super weapons.
/// A super weapon that depends on a building is suspended while that building is shut
/// down or the base is short of power, and taken away entirely once the building is gone
/// or the house has been defeated. The sidebar is flagged for redraw and any targeting
/// mode cancelled when the local player is the one affected.
/// </summary>
void HouseClass::Update_Present_Super_Weapons(void)
{
	if (GameActive) {
		bool is_player = PlayerPtr == this; // RA2: whether this is the player's house is decided once, by house pointer
		for (int s = 0; s < SuperWeapon.Count(); s++) {
			if (SuperWeapon[s]->Is_Present() && ((SuperWeapon[s]->NeedsBuilding && !SuperWeapon[s]->Is_One_Time()) || IsDefeated)) {
				bool present = false;
				bool enabled = false;
				if (!IsDefeated) {
					for (int j = 0; j < ::Buildings.Count(); j++) { // RA2: every building in the game is looked at, the house test is on the building
						BuildingClass * b = ::Buildings[j]; // RA2: as above
						bool is_active = !b->IsInLimbo && b->IsActive;
						if (is_active && b->House->Fetch_ID() == Fetch_ID()) {
							for (int k = 0; k < 3; k++) {
								BuildingTypeClass const * upgrade = b->Upgrades[k];
								if (upgrade != NULL && (upgrade->SuperWeapon == s || upgrade->SuperWeapon2 == s)) {
									present = true;
									if (!enabled) enabled = b->IsOn;
								}
							}
							if (b->Fetch_Super_Weapon() == s || b->Fetch_Super_Weapon2() == s) {
								present = true;
								if (enabled) break;
								enabled = b->IsOn;
							}
							if (enabled && present) break;
						}
					}
				}

				int power = Power;
				int drain = Drain;
				if (power < drain && drain != 0) {
					if (power == 0 || (double)power / (double)drain < 1.0) {
						enabled = false;
					}
				}

				int type_index = SuperWeapon[s]->Class->Fetch_Heap_ID(); // level-2 1.001: the heap id is fetched before the push of false (0x4F41CB)
				int tab = SidebarClass::Which_Tab(RTTI_SUPERWEAPON, type_index, false); // RA2: the sidebar tab of the weapon is redrawn, not just the second column

				if (present && !IsDefeated) {
					bool suspended = !enabled && SuperWeapon[s]->Is_Powered() && SuperWeapon[s]->Suspend(true);
					bool resumed = enabled && SuperWeapon[s]->Suspend(false);
					if (suspended || resumed) {
						if (is_player) { // RA2: as above
							if (Map.IsTargettingMode == s) {
								Map.IsTargettingMode = SUPER_NONE;
							}
							Map.Flag_Tab_To_Redraw(tab); // RA2: as above
						}
						IsRecalcNeeded = true;
					}
				} else {
					if (SuperWeapon[s]->Remove() && PlayerPtr != NULL) {
						if (is_player) { // RA2: as above
							if (Map.IsTargettingMode == s) {
								Map.IsTargettingMode = SUPER_NONE;
							}
							Map.Flag_Tab_To_Redraw(tab); // RA2: as above
						}
						IsRecalcNeeded = true;
					}
				}
			}
		}
	}
}
