// RA2 1.001 byte-identical (VC6 8168 /O2 /Ob2 /Gr /GR /Gy), RVA 0x231e10, from our src/m85/src/reinf.cpp. GPL-3.0-or-later.
// Your 1.006 entry 0x0063A880 (Do_Chrono_Reinforcements, 1567 bytes, non_exact in your map).

bool Do_Chrono_Reinforcements(TeamTypeClass const * teamtype, WAYPOINT wp)
{
	if (!teamtype || !teamtype->TaskForce->ClassCount) return(false);

	ScriptTypeClass * script = teamtype->Script;
	if (!script || script->MissionCount == 0) {
		TeamMissionClass tmission(TMISSION_GUARD, 0);
		if (!script) {
			((TeamTypeClass *)teamtype)->Script = new ScriptTypeClass(NULL);
		}
		script = teamtype->Script;
		int count = script->MissionCount;
		if (count < MAX_TEAM_MISSIONS) {
			script->MissionList[count] = tmission;
			script->MissionCount++;
		}
	}

	FootClass * group = _Create_Group(teamtype);
	group->Team->IsDeleteTypeWhenDone = false;
	if (!group) {
		return(false);
	}

	Cell origin = teamtype->Get_Origin();
	if (wp != -1) {
		origin = Scen->Get_Waypoint_Cell(wp);
	}

	FootClass * object = group; // level-2 1.001: STEERING
	FootClass * next = (FootClass *)(ObjectClass *)object->Next;
	object->Next = NULL;
	FootClass * placed = NULL;

	while (object != NULL) {
		bool isunit = false;
		if (object != NULL && object->Fetch_RTTI() == RTTI_UNIT) {
			isunit = true;
		}

		Coord coord = Map[origin].Center_Coord();
		if (!isunit) {
			coord.X += ((object->Ammo & 3) - 2) << 8; // RA2: the x offset is scaled by 256, the y offset by 64 (shl 8 / shl 6)
			coord.Y += ((object->Ammo & 0xC) - 4) << 6;
		}
		object->Ammo--;

		Coord dest = COORD_NONE;
		CellClass * cellptr = &Map[coord];
		int tries = 0;
		while (dest == COORD_NONE && tries < 255) {
			Cell nearcell = Map.Nearby_Location(cellptr->Center_Coord().As_Cell(), object->Techno_Type_Class()->Speed);
			cellptr = &Map[nearcell];
			if (isunit) {
				dest = cellptr->Center_Coord();
			} else {
				dest = cellptr->Closest_Free_Spot(cellptr->Center_Coord());
			}
			tries++;
		}

		coord.X = dest.X;
		coord.Y = dest.Y;
		ScenarioInit++;
		int ok = object->Unlimbo(coord, DIR_N);
		ScenarioInit--;
		if (ok) {
			IPiggybackPtr piggy(object->Locomotion);
			ILocomotionPtr teleport(CLSID_TeleportLocomotion);
			teleport->Link_To_Object(object);
			piggy = IPiggybackPtr(teleport);
			if (piggy != NULL) {
				piggy->Begin_Piggyback(object->Locomotion);
				object->Locomotion = teleport;
			}
			object->ChronoDestCoords = coord;
			object->Locomotion->Move_To(coord);
			object->WarpingOut = true;
			object->ChronoLockRemaining = Rule->ChronoReinfDelay;
			Prepend_Reinforcement(object, placed);
			object = next;
			if (object != NULL) {
				next = (FootClass *)(ObjectClass *)object->Next;
				object->Next = NULL;
			}
		} else {
			delete object;
			object = next;
			if (object != NULL) {
				next = (FootClass *)(ObjectClass *)object->Next;
				object->Next = NULL;
			}
		}
	}

	object = placed;
	placed = (FootClass *)(ObjectClass *)object->Next;
	object->Next = NULL;
	while (object != NULL) {
		object->Mark(MARK_UP);
		object->TeleportState = 3;
		object->Commence();
		object = placed;
		if (object != NULL) {
			placed = (FootClass *)(ObjectClass *)object->Next;
			object->Next = NULL;
		}
	}

	if (teamtype->House->Is_Ally(PlayerPtr)) {
		Record_Radar_Event_Cell(origin); // level-2 1.001: stores the last event cell (1.006 records it in a ring)
	}
	return(true);
}
