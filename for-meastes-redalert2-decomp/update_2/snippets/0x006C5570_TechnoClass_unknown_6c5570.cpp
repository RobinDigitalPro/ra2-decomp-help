// RA2 1.001 byte-identical (VC6 8168 /O2 /Ob2 /Gr /GR /Gy), RVA 0x2baba0, from our src/m85/src/techno.cpp. GPL-3.0-or-later.
// Your 1.006 entry 0x006C5570 (TechnoClass::unknown_6c5570, 2998 bytes, non_exact in your map).

bool TechnoClass::Evaluate_Object(ThreatType method, int mask, int range, TechnoClass const * object, int & value, int zone, Coord const & coord) const
{
	// level-2 1.001: rewritten in 1.001's order (gibbo101 YR CanAutoTargetObject without the YR features)
	bool engineer = Is_Renovator();
	int which = What_Weapon_Should_I_Use((AbstractClass *)object);
	WeaponTypeClass const * weapon = Get_Class_Weapon_Data(which)->Weapon;

	if (!(method & (THREAT_CAPTURE|THREAT_OCCUPIABLE|THREAT_TECH_BUILDINGS)) && GetFireErrorWithoutRange((AbstractClass *)object, which) == 5) return(false);
	if (object->EstimatedHealth <= 0 && TClass->VHPScan == 2) return(false);

	/*
	**	A warhead that does 1% against the target's armor never picks it automatically.
	*/
	if (weapon != NULL && weapon->WarheadPtr != NULL && (int)(weapon->WarheadPtr->Modifier[object->TClass->Armor] * 100) == 1) return(false);

	/*
	**	An object in limbo can never be a valid target.
	*/
	if (object == NULL || object->IsInLimbo || object->Strength == 0) {
		return(false);
	}

	/*
	**	If the object is cloaked, then it isn't a legal target.
	*/
	if (object->Cloak == CLOAKED) {
		if (!Map[object->Center_Coord()].Is_Sensed(House->HeapID) && House != object->House) return(false);
	}

	if (!object->IsLocked) return(false);

	/*
	**	If the object is in a "harmless" state, then don't bother to consider it
	**	a threat.
	*/
	if (object->Current_Mission_Control().IsNoThreat) return(false);
	if (object->HeightAGL < -20) return(false);

	/*
	**	If the object is not within the desired zone, then ignore it, but only if
	**	zone checking is desired.
	*/
	Coord objectcoord = object->Center_Coord();
	if (zone != -1 && Map.Get_Cell_Zone(objectcoord.As_Cell(), TClass->MZone, object->IsOnBridge) != zone) return(false);

	/*
	**	Friendly units are never considered a good target. Bail if this
	**	object is a friend.  Unless we're a medic, of course.  But then,
	**	only consider it a target if it's injured.
	*/
	if ((RTTI != RTTI_INFANTRY || !((InfantryClass *)this)->IsBerzerk) && !TClass->AttackFriendlies && House->Is_Ally(object)) {
		if (Combat_Damage() < 0 || engineer) {
			if (object->HealthRatio == Rule->ConditionGreen) return(false);
			if (object->RTTI == RTTI_AIRCRAFT && RTTI == RTTI_UNIT) {
				if (object->HeightAGL > 0) return(false);
				if (Map[object->Center_Coord()].Cell_Building()) return(false);
			} else if (RTTI == RTTI_UNIT && !object->Considered_Vehicle()) {
				return(false);
			}
		} else {
			return(false);
		}
	}

	if (Scen->Special.IsHarvesterImmune && Rule->HarvesterUnit.Is_In_List((UnitTypeClass const *)object->Class_Of())) return(false);

	/*
	**	If the object is further away than allowed, bail.
	*/
	int dist;
	if (object->In_Air()) {
		double x = object->Center_Coord().X - Center_Coord().X;
		double y = object->Center_Coord().Y - Center_Coord().Y;
		dist = fastmath::sqrt(x * x + y * y);
		if (range > 0 && dist > range) return(false);
	} else {
		Coord separation = Center_Coord() - object->Center_Coord();
		double y = separation.Y;
		double z = separation.Z;
		double x = separation.X;
		dist = fastmath::sqrt(x * x + z * z + y * y);
		if (range > 0 && dist > range) return(false);
	}

	if (range == 0) {
		if (!Is_Weapon_Equipped()) {
			if (dist > TClass->ThreatRange) return(false);
		} else {
			if (!In_Range((AbstractClass *)object, which)) return(false);
		}
	}

	/*
	**	If the object is not visible, then bail. Human controlled units
	**	are always considered to be visible.
	*/
	if (House->Is_Player_Control() && !object->IsOwnedByPlayer && !object->IsDiscoveredByPlayer && Session.Type == GAME_NORMAL && object->RTTI != RTTI_AIRCRAFT) return(false);
	if (object->RTTI == RTTI_BUILDING && ((BuildingClass *)object)->Class->IsInvisibleInGame) return(false);

	/*
	**	Quickly eliminate all unit types that are not allowed according to the mask
	**	value.
	*/
	RTTIType otype = object->RTTI;
	if (!((1 << otype) & mask) && (!(mask & 2) || !object->Considered_Vehicle())) return(false);		// Mask failure.

	/*
	**	Determine if the target is theoretically allowed to be a target. If
	**	not, then bail.
	*/
	TechnoTypeClass const * tclass = object->TClass;
	if (!tclass->IsLegalTarget) return(false);		// Legality failure.

	if (Session.Type != GAME_NORMAL && object->House->Class->IsMultiplayPassive) {
		if (!Can_Capture_Passive_Target(this, object)) return(false);
	}
	if (tclass->IsInsignificant && (object->RTTI != RTTI_BUILDING || object->House->Class->IsMultiplayPassive)) {
		if (!Can_Capture_Passive_Target(this, object)) return(false);
	}

	if (tclass->IsTrain && RTTI == RTTI_INFANTRY && ((InfantryClass *)this)->Class->IsVehicleThief) return(false);

	/*
	**	A disguised object is only seen through now and then, unless this object detects disguises.
	*/
	if (object->IsDisguisedAs(House) && !TClass->DetectDisguise) {
		if (object->DisguiseBlinkTimer == 0 || House->Is_Human_Player() || Random_Pick(0, 99) > Rule->DisabledDisguiseDetectionPercent[House->Difficulty]) {
			return(false);
		}
	}

	/*
	**	If only allowed to attack civilians, then eliminate all other types.
	*/
	if (method & THREAT_CIVILIANS) {
		object->Owner_HouseClass(); /// The result is unused.
		return(false);
	}

	/*
	**	If the scan is limited to capturable buildings only, then bail if the examined
	**	object isn't a capturable building.
	*/
	if ((method & THREAT_CAPTURE) && (otype != RTTI_BUILDING || !((BuildingTypeClass const *)tclass)->IsCaptureable)) return(false);

	/*
	**	SPECIAL CASE: Friendly units won't automatically fire on buildings
	**	if the building is not aggressive. That is, unless it is part of a team. A team
	**	is allowed to pick any target it so chooses.
	*/
	if ((!Is_Foot() || ((FootClass *)this)->Team == NULL) && House->Is_Human_Player() && !object->Considered_Vehicle() && otype == RTTI_BUILDING) {
		WeaponDataStruct const * turret = object->GetTurretWeapon();
		if (turret == NULL || turret->Weapon == NULL || object->TClass->Risk == 0) {
			if (!engineer) return(false);
		}
	}

	if (engineer) {
		if (object->RTTI != RTTI_BUILDING || (House->Is_Ally(object->House) && (object->HealthRatio > Rule->ConditionRed || !((BuildingClass *)object)->Class->Cost_Of(House)))) {
			return(false);
		}
	}

	/*
	**	If the search is restricted to Tiberium processing objects, then
	**	perform the special qualification check now.
	*/
	if ((method & THREAT_TIBERIUM) && tclass->Capacity == 0) return(false);

	CellClass * cell_this = &Map[Get_Coord()];
	CellClass * cell_that = &Map[object->Get_Coord()];
	if (cell_this->IsUnderBridge && cell_that->IsUnderBridge && IsOnBridge != object->IsOnBridge) return(false);

	/*
	**	If this target value is better than the previously recorded best
	**	target value then record this target for possible return as the
	**	best.
	*/
	value = Target_Threat((TechnoClass *)object, coord);
	if (TClass->VHPScan == 1) {
		if (object->EstimatedHealth <= 0) {
			value /= 2;
		} else if (object->EstimatedHealth <= object->TClass->MaxStrength / 2) {
			value *= 2;
		}
	}

	/*
	**	If the candidate object is owned by the designated enemy of this house, then
	**	give it a higher value. This will tend to gravitate attacks toward the main
	**	antagonist of this house.
	*/
	if (House->IsAllToHunt && House->Enemy != HOUSE_NONE && object->House != Houses[House->Enemy]) {
		value = 1;
	}

	/*
	**	If power plants are to be considered a greater threat, then increase
	**	their value here. Buildings that produce no power are not considered
	**	a threat.
	*/
	if ((method & THREAT_POWER) && otype == RTTI_BUILDING) {
		if (((BuildingTypeClass const *)tclass)->Power > 0) {
			value += ((BuildingTypeClass const *)tclass)->Power * 1000;
		} else {
			value = 0;
		}
	}

	/*
	**	Occupiable and tech building scans only accept such buildings.
	*/
	if (method & THREAT_OCCUPIABLE) {
		if (otype != RTTI_BUILDING || ((BuildingTypeClass const *)tclass)->MaxNumberOccupants <= 0) return(false);
		value += ((BuildingTypeClass const *)tclass)->MaxNumberOccupants * 1000;
	}

	if (method & THREAT_TECH_BUILDINGS) {
		if (otype != RTTI_BUILDING || !((BuildingTypeClass const *)tclass)->NeedsEngineer) return(false);
		value += 1000;
	}

	/*
	**	If factories are to be considered a greater threat, then don't
	**	consider any non-factory building.
	*/
	if ((method & THREAT_FACTORIES) && otype == RTTI_BUILDING && ((BuildingTypeClass const *)tclass)->ToBuild == RTTI_NONE) {
		value = 0;
	}

	/*
	**	If base defensive structures are to be considered a greater threat, then
	**	don't consider an unarmed building or an empty occupiable one to be a threat.
	*/
	if (method & THREAT_BASE_DEFENSE) {
		WeaponDataStruct const * turret = GetTurretWeapon();
		if (turret != NULL && turret->Weapon != NULL && otype == RTTI_BUILDING) {
			BuildingClass * building = As_Building((AbstractClass *)object);
			if (building->Class->CanBeOccupied && building->GetOccupantCount() == 0) {
				value = 0;
			}
		} else {
			value = 0;
		}
	}

	/*
	**	Possibly cause a reduction of the target's value if it is nearby friendly
	**	structures and the primary weapon of this object is flagged for
	**	friendly fire supression special check logic.
	*/
	double areamod = Area_Modify(object->Center_Coord().As_Cell());
	if (areamod != 1) {
		value = areamod * value;
	}

	/*
	**	Lessen threat as a factor of distance.
	*/
	if (value) {
		value = MAX(1, value);
		return(true);
	}
	value = 0;
	return(false);
}
