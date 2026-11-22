// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00637D00 (164 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20c680 (VA 0x0060C680, 176 bytes incl. padding)
// RA2 symbol : ?Send_Delete_Event@PlanningNodeClass@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9016)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void PlanningNodeClass::Send_Delete_Event(void) // RA2: 0x00614AA0
{
	EventClass event = *PlanningMembers[0]->Packet; // RA2: as above
	xTargetClass * target; // RA2: as above
	if (event.Data.MegaMission.Target.Is_Valid()) { // RA2: as above
		target = &event.Data.MegaMission.Target; // RA2: as above
	} else if (event.Data.MegaMission.Follow.Is_Valid()) { // RA2: as above
		target = &event.Data.MegaMission.Follow; // RA2: as above
	} else if (event.Data.MegaMission.Destination.Is_Valid()) { // RA2: as above
		target = &event.Data.MegaMission.Destination; // RA2: as above
	} else { // RA2: as above
		return; // RA2: as above
	}
	AbstractClass * object = target->As_Abstract(); // RA2: as above
	if (object) { // RA2: as above
		EventClass remove(PlayerPtr->HeapID, EventClass::PLAN_NODE_DELETE, TargetClass(object)); // RA2: as above
		Add_Outgoing_Event(remove); // RA2: as above
	}
}
