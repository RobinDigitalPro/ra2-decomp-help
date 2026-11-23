// redalert2-decomp help snippet, package 1 (RA2 1.001 level-2 reconstruction; NOT verified on RA2 1.006)
// Function    : Planning_Execute
// Symbol      : ?Planning_Execute@@YIXPAVEventClass@@@Z (the same in both projects)
// Our address : RA2 1.001 GAME.EXE, RVA 0x20c780 (VA 0x0060C780); source TU src/m85/src/planmgr.cpp
// Your address: RA2 1.006, 0x00614BA0 (786 bytes), src/recovered/planmgr.cpp; manifests/function_map.csv: non_exact, score 78.17
// Evidence    : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
//               (compared after masking relocation operands).
// Caution     : 1.001 and 1.006 may differ in this body. Comments of the form "RA2: 0x..." name
//               1.006 addresses; "level-2 1.001:" comments describe what the 1.001 bytes needed.
// License     : GPL-3.0-or-later. Credits carried by this code:
//               - Electronic Arts (GPL source releases; section 7 additional terms)
//               - OpenTS contributors and mischa85/RedAlert2 (the RA2 1.006 tree our source started from)
//               - gibbo101/ra2-decomp (forms adopted in this body; see the comments in it)
//               The notice of our source file follows. Please keep notices and credits.
// Use         : a read-only lead with our layouts and names. Port the idea; let your checker decide.

/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * Contains material derived from Electronic Arts source code.
 * Modified by OpenTS contributors, 2026.
 * EA's GPLv3 Section 7 additional terms and supplemental warranty
 * disclaimers apply; see LICENSE.md.
 ******************************************************************************/

void __fastcall Planning_Execute(EventClass * event) // RA2: 0x00614BA0; carries out a planning event: plan commit restarts the paths of the event's house, plan connect adds the node at the second target's coordinate to the first target's path, plan node delete takes the node at the target's coordinate out of every path (remembering the next node for the player); any other event is an order for its techno
{
	if (event->Type == EventClass::PLAN_COMMIT) { // RA2: as above
		Commit_Plans(event->ID); // RA2: as above
	} else if (event->Type == EventClass::PLAN_CONNECT) { // RA2: as above
		TechnoClass * techno = event->Data.NavCom.Whom.As_Techno(); // RA2: as above
		if (techno) { // RA2: as above
			AbstractClass * object = event->Data.NavCom.Where.As_Abstract(); // RA2: as above
			if (object) { // RA2: as above
				// level-2 1.001: structure of gibbo101/ra2-decomp src/planmgr.cpp @94adbad041 FUN_00637E00 (both branches through the finder 0x20db90,
				// Member_Owner, the named token and Set_Selected_Node); the connect coordinate is assigned after its default
				// construction (as gibbo's Lead_At writes it), which cuts the Has_Started of the inlined Commit_Plans as in 1.001
				Coord coord; // RA2: as above
				coord = object->As_Coord(); // RA2: as above
				PlanningNodeClass * node = Planning_Find_Node(event->ID, -1, coord); // RA2: as above
				if (node) { // RA2: as above
					Planning_Path_Add(techno, node); // RA2: as above
				}
			}
		}
	} else if (event->Type == EventClass::PLAN_NODE_DELETE) { // RA2: as above
		AbstractClass * object = event->Data.Target.Whom.As_Abstract(); // RA2: as above
		if (object) { // RA2: as above
			Coord coord = object->As_Coord(); // RA2: as above
			int house = event->ID; // RA2: as above
			PlanningNodeClass * node = Planning_Find_Node(house, -1, coord); // RA2: as above; level-2 1.001: the finder again (0x20c780 calls Lead_At and Planning_House out of line in this copy)
			if (node) { // RA2: as above
				TechnoClass * owner = node->Member_Owner(0); // RA2: as above
				int index = node->Index_In(owner); // RA2: as above; level-2 1.001: through Index_In (0x20c780 then calls Node_At out of line, as 1.001 does)
				PlanningTokenClass * token = owner->Get_Planning_Token(); // RA2: as above
				PlanningNodeClass * next = token->Node_At(index + 1); // RA2: as above
				Planning_Remove_Node(node); // RA2: as above
				if (next && house == PlayerPtr->HeapID) { // RA2: as above
					Planning_Set_Selected_Node(next); // RA2: as above
				}
			}
		}
	} else { // RA2: as above
		TechnoClass * techno = event->Data.Target.Whom.As_Techno(); // RA2: as above
		Planning_Add_Order(techno, event); // RA2: as above
	}
}

// ---- helper: forward declarations used by the function (src/m85/src/planmgr.cpp) ----
void __fastcall Planning_Add_To_Nodes(PlanningNodeClass * node); // RA2: 0x00615B60
void __fastcall Planning_Set_Pending_Refusal(int value); // RA2: 0x00617240
PlanningTokenClass * __fastcall Planning_New_Token(TechnoClass * techno); // RA2: 0x00615820
void __fastcall Planning_Close_Loop(TechnoClass * techno, PlanningNodeClass * node); // RA2: 0x006164E0
void __fastcall Planning_Path_Add(TechnoClass * techno, PlanningNodeClass * node); // RA2: 0x00616350
PlanningNodeClass * __fastcall Planning_Find_Node(int house, int id, Coord coord); // RA2: 0x00615FB0
void __fastcall Planning_Cancel_Token(TechnoClass * techno); // RA2: 0x006155E0
bool __fastcall Planning_Same_Last_Node(PlanningTokenClass * first, PlanningTokenClass * second); // RA2: 0x00616BD0
void __fastcall Planning_Set_Selected_Node(PlanningNodeClass * node); // RA2: 0x00617E20

// ---- helper: Commit_Plans, expanded inline in Planning_Execute in 1.001 (src/m85/src/planmgr.cpp) ----
void __fastcall Commit_Plans(int house) // RA2: 0x00614850; for every object of a house: starts the path again when it is not under way and its mission allows it; the expansion of TechnoClass::TryNextPlanningTokenNode (0x00615360) and of Planning_Mission_Allows stand in it
{
	int count = Technos.Count(); // RA2: as above
	for (int i = 0; i < count; i++) { // RA2: as above
		TechnoClass * techno = Technos[i]; // RA2: as above
		if (house == Planning_House(techno)) { // RA2: as above
			PlanningTokenClass * token = techno->Get_Planning_Token(); // RA2: as above
			if (token != NULL) { // RA2: as above
				bool started = token->Has_Started(); // RA2: as above
				token->Reset_Node_Colors(); // RA2: as above
				bool permitted = Planning_Mission_Allows(techno); // RA2: as above
				if (!started && permitted) { // RA2: as above
					techno->TryNextPlanningTokenNode(); // RA2: as above
				}
			}
		}
	}
}

// ---- helper: PlanningNodeClass::Index_In, expanded inline in 1.001 (src/m85/src/planmgr.cpp) ----
int PlanningNodeClass::Index_In(TechnoClass * techno) // RA2: 0x00610C30
{
	PlanningTokenClass * token = techno->Get_Planning_Token(); // RA2: as above
	return token->PlanningNodes.ID(this); // RA2: as above
}

// ---- helper: PlanningNodeClass::Member_Owner (src/m85/src/planmgr.cpp) ----
TechnoClass * PlanningNodeClass::Member_Owner(int index) // RA2: 0x00611090
{
	PlanningMemberClass * member = PlanningMembers[index]; // RA2: as above; level-2 1.001: a named member, as gibbo101's YR source (Draw_Filled_Node then calls Member_Owner out of line)
	return member->Owner; // RA2: as above
}
