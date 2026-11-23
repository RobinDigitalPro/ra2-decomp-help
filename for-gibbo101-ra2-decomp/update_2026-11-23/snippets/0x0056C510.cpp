// ra2-decomp help snippet, update 2026-11-23 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0056C510 (1646 bytes; gibbo101/ra2-decomp name: MapClass::Update_Pathfinding_1)
// RA2 address: RVA 0x14c060 (VA 0x0054C060, 1646 bytes without padding)
// RA2 symbol : ?Zone_Reset@MapClass@@QAEHXZ
// similarity : 0.9342 (similar, masked instruction tokens; shape 0.9982)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/map.cpp
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

/***********************************************************************************************
 * MapClass::Zone_Reset -- Resets all zone numbers to match the map.                           *
 *                                                                                             *
 *    This routine will rescan the map and fill in the zone values for each of the cells.      *
 *    All cells that are contiguous are given the same zone number.                            *
 *                                                                                             *
 * INPUT:   method   -- The method to recalculate the zones upon. If 1 then recalc non         *
 *                      crushable zone. If 2 then recalc crushable zone. If 3, then            *
 *                      recalc both zones.                                                     *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   This is a time consuming routine. Call it as infrequently as possible. It must  *
 *             be called whenever something that would affect contiguousness occurs. Example:  *
 *             when a bridge is built or destroyed.                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/22/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
int MapClass::Zone_Reset(void)
{
	int i;
	int j;
	int k;
	int bestzone = -1;
	int bestspan = -1;

	CellZoneStruct * end = &CellZones[CellZoneCount];

	DynamicVectorClass<PassabilityType> vec;
	vec.Set_Growth_Step(300);

	ZoneAdjacency->Clear();

	for (i = 0; i < MZONE_CRUSHER_ALL; i++) { // RA2: as above
		if (Zones[i] != NULL) {
			delete Zones[i];
			Zones[i] = NULL;
		}
	}

	CellZoneStruct * czone = CellZones;
	for (; czone < end; czone++) {
		czone->ZoneID = 0;
	}

	int zone = 1;			// Starting zone number.

	vec.Add(PASSABLE_OUTSIDE);

	int skip = 0;
	czone = CellZones;
	while (czone < end) {
		PassabilityType pass = (PassabilityType)czone->Passability;
		if (pass != PASSABLE_OUTSIDE && czone->ZoneID == 0) {
			LastAdjacentZone = 0;
			int span = Zone_Span(czone, zone, skip);
			if (span > bestspan) {
				bestzone = (unsigned short)zone;
				bestspan = span;
			}
			vec.Add(pass);
			zone++;
			czone += skip;
		} else {
			czone++;
		}
	}

	ZoneCount = (unsigned short)zone;

	for (i = ZoneConnections.Count() - 1; i >= 0; i--) {
		if (!ZoneConnections[i].IsPassable) { // level-2 1.001: indexed access and continue instead of a wrapping if (register choice of the original)
			continue;
		}
		int from_zone = Get_Cell_Zone_ID(ZoneConnections[i].From);
		int to_zone = Get_Cell_Zone_ID(ZoneConnections[i].To);
		if (to_zone != from_zone) {
			if (to_zone < from_zone) {
				swap(to_zone, from_zone);
			}
			ZoneAdjacency->Add_Object(ZONE_PAIR_HASH_SET::ObjectType(from_zone, to_zone));
		}
	}

	unsigned short * zone_degree = new unsigned short[ZoneCount];
	for (i = 0; i < ZoneCount; i++) {
		zone_degree[i] = 0;
	}

	for (i = 0; i < 256; i++) {
		ZONE_PAIR_HASH_SET::BucketType & bucket = ZoneAdjacency->Buckets[i];
		j = bucket.Count();
		if (j > 0) {
			ZONE_PAIR_HASH_SET::ObjectType * obj = &bucket[0];
			do {
				unsigned int value = obj->Value;
				unsigned short zone1 = LOWORD(value);
				unsigned short zone2 = HIWORD(value);
				zone_degree[zone1]++;
				zone_degree[zone2]++;
				obj++;
			} while (--j);
		}
	}

	unsigned short ** zone_neighbors = new unsigned short *[ZoneCount];
	for (i = 0; i < ZoneCount; i++) {
		zone_neighbors[i] = new unsigned short[zone_degree[i]];
	}

	for (i = 0; i < ZoneCount; i++) {
		zone_degree[i] = 0;
	}

	for (i = 0; i < 256; i++) {
		ZONE_PAIR_HASH_SET::BucketType & bucket = ZoneAdjacency->Buckets[i];
		if (bucket.Count() > 0) {
			ZONE_PAIR_HASH_SET::ObjectType * obj = &bucket[0];
			for (j = bucket.Count(); j > 0; j--) { // level-2 1.001: count tested before it is stored
				unsigned int value = obj->Value;
				unsigned short zone1 = LOWORD(value);
				unsigned short zone2 = HIWORD(value);
				zone_neighbors[zone1][zone_degree[zone1]] = zone2;
				zone_neighbors[zone2][zone_degree[zone2]] = zone1;
				zone_degree[zone1]++;
				zone_degree[zone2]++;
				obj++;
			}
		}
	}

	unsigned char * zone_passability = new unsigned char[ZoneCount];
	for (i = 0; i < ZoneCount; i++) {
		zone_passability[i] = vec[i];
	}

	unsigned short * stack = new unsigned short[ZoneCount];

	for (MZoneType mzone = MZONE_FIRST; mzone < MZONE_CRUSHER_ALL; mzone++) { // RA2: as above
		int next_movement_zone = 2;
		int * table = MZonePassability[mzone];

		unsigned short * nzone = new unsigned short[ZoneCount];
		Zones[mzone] = nzone;

		for (int n = 0; n < ZoneCount; n++) { // level-2 1.001: loop-local counter (address operand order)
			nzone[n] = table[zone_passability[n]] != TRAVERSAL_PASSABLE;
		}

		for (int zone_index = 0; zone_index < ZoneCount; zone_index++) {
			if (nzone[zone_index] == 0) {
				int stackcount = 1;
				stack[0] = zone_index;
				nzone[zone_index] = next_movement_zone;
				int passable = table[zone_passability[zone_index]];
				while (stackcount) {
					int current = stack[--stackcount];
					unsigned short * neighbors = zone_neighbors[current];
					int degree = zone_degree[current];
					for (k = degree - 1; k >= 0; k--) {
						int neighbor = neighbors[k];
						if (table[zone_passability[neighbor]] == passable && nzone[neighbor] == 0) {
							stack[stackcount++] = neighbor;
							nzone[neighbor] = next_movement_zone;
						}
					}
				}
				next_movement_zone++;
			}
		}

		nzone[0] = -1;
	}

	for (i = 0 ; i < ZoneCount; i++) {
		delete zone_neighbors[i];
	}

	delete [] zone_passability;
	delete [] zone_neighbors;
	delete [] zone_degree;
	delete [] stack;

	return(bestzone); // level-2 1.001: returns the best zone number itself
}
