// ra2-decomp help snippet, update 2026-11-23 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00638120 (1181 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0x20caa0 (VA 0x0060CAA0, 1181 bytes without padding)
// RA2 symbol : ?Planning_Add_Order@@YI_NPAVTechnoClass@@PAVEventClass@@@Z
// similarity : 0.9782 (very-similar, masked instruction tokens; shape 1.0000)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/planmgr.cpp
// License    : GPL-3.0-or-later. Our source is GPL and contains EA GPL code (section 7 terms)
//              and code adapted from mischa85/RedAlert2 and gibbo101/ra2-decomp; their
//              credits are kept. The notice of the source file follows. See ../README.md.
// Use        : a read-only lead. RA2 layouts and names; port it and match it on your own checker.

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

bool __fastcall Planning_Add_Order(TechnoClass * techno, EventClass * event) // RA2: 0x00614EC0; plans an order for a techno: adds it to the node at the order's coordinate, or to a new node, unless the order or the techno's path refuses it
{
	if (!techno) { // RA2: as above
		return false; // RA2: as above
	}
	bool player = event->ID == PlayerPtr->HeapID; // RA2: as above
	Coord const & coord = Planning_Event_Coord(*event); // RA2: as above
	if (coord == Coord(-1, -1, -1)) { // RA2: as above
		return false; // RA2: as above
	}
	int id = event->Frame; // RA2: as above
	PlanningNodeClass * node = Planning_Find_Lead_Node(event->ID, id, coord); // RA2: as above
	if (node && node->Has_Member(techno)) { // RA2: as above
		return true; // RA2: as above
	}
	int kind = Planning_Order_Kind(techno, (PlanningEventTargets const *)event); // RA2: as above
	if (kind != -1) { // RA2: as above
		if (!player) { // RA2: as above
			return false; // RA2: as above
		}
		if (kind == 0) { // RA2: as above
			Planning_Refuse_Order(event); // RA2: as above
		} else if (kind == 1) { // RA2: as above
			Planning_Refuse("MSG:PostTerminatingCommand"); // RA2: as above
		} else if (kind == 2) { // RA2: as above
			Planning_Refuse("MSG:PostContinualCommand"); // RA2: as above
		}
		return false; // RA2: as above
	}
	PlanningTokenClass * token = techno->Get_Planning_Token(); // RA2: as above
	if (!token) { // RA2: as above
		token = Planning_New_Token(techno); // RA2: as above
	}
	if (player) { // RA2: as above
		int result = Planning_Event_Result(token, (PlanningEventTargets const *)event); // RA2: as above
		if (result != -1) { // RA2: as above
			Planning_Set_Pending_Refusal(result); // RA2: as above
		}
	}
	if (Planning_Token_Looped(token)) { // RA2: as above
		if (player) { // RA2: as above
			Planning_Refuse("MSG:PostLoop"); // RA2: as above
		}
		return false; // RA2: as above
	}
	if (token->Node_Count() == 0) { // RA2: as above
		PlanningTokenClass::Technos.Add(techno); // RA2: as above
		Planning_Recount(event->ID); // RA2: as above
	} else if (token->Node_Count() == 16) { // RA2: as above
		if (player) { // RA2: as above
			Planning_Refuse("MSG:NodeMaximum"); // RA2: as above
		}
		return false; // RA2: as above
	}
	if (!node) { // RA2: as above
		node = new PlanningNodeClass(event->Frame); // RA2: as above
		PlanningNodeClass::Unknown1.Add(node);
	}
	if (!Planning_Copy_Last(token, node, event)) {
		node->Add_Member(techno, event);
	}
	if (player) { // RA2: as above
		VocClass::PlayGlobal(Rule->AddPlanningModeCommandSound, 1.0f, 0x2000); // RA2: as above
	}
	return true; // RA2: as above
}
