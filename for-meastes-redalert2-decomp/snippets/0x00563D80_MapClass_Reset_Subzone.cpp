// redalert2-decomp help snippet, package 1 (RA2 1.001 level-2 reconstruction; NOT verified on RA2 1.006)
// Function    : MapClass::Reset_Subzone
// Symbol      : ?Reset_Subzone@MapClass@@QAEXH@Z (the same in both projects)
// Our address : RA2 1.001 GAME.EXE, RVA 0x160b70 (VA 0x00560B70); source TU src/m85/src/map.cpp
// Your address: RA2 1.006, 0x00563D80 (1287 bytes), src/recovered/map.cpp; manifests/function_map.csv: non_exact, score 76.89
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
 * Copyright 2025 Electronic Arts Inc.
 * Copyright 2026 OpenTS contributors
 *
 * Contains material derived from Electronic Arts source code.
 * Modified by OpenTS contributors, 2026.
 * EA's GPLv3 Section 7 additional terms and supplemental warranty
 * disclaimers apply; see LICENSE.md.
 ******************************************************************************/

/// <summary>
/// Rebuilds one level of the subzone graph from scratch.
/// Every cell of the play area is sorted into a fresh subzone and the bridge and tunnel links
/// are stitched back in, leaving the hierarchical path search a graph it can trust. Use this
/// routine when the map has changed too much to be patched cell by cell.
/// </summary>
/// <param name="subzone">The subzone level to rebuild.</param>
void MapClass::Reset_Subzone(int subzone)
{ // level-2: adopted from gibbo101 src/map.cpp @719fcc7
	CellSubzoneStruct * subend = &CellSubzones[CellZoneCount];
	SUBZONE_CONNECTION_HASH_SET * set = SubzoneConnectionHashTable[subzone];
	DynamicVectorClass<SubzoneTrackingStruct> * track = &SubzoneTracking[subzone];
	set->Clear();

	CellSubzoneStruct * subptr = CellSubzones;
	CellZoneStruct * zoneptr = CellZones;
	if (subptr < subend) {
		do {
			subptr->SubzoneID[subzone] = 0;
			subptr->ZoneID = zoneptr->ZoneID;
			subptr->Height = zoneptr->Height;
			subptr++;
			zoneptr++;
		} while (subptr < subend);
	}

	int entry_count = 1;
	track->Add(SubzoneTrackingStruct());
	(*track)[0].ParentSubzoneID = 0;
	(*track)[0].Passability = PASSABLE_OUTSIDE;

	subptr = CellSubzones;
	zoneptr = CellZones;
	int regionmask = (1 << (subzone + 1)) - 1;
	int rowwidth = Map.PlayRect.Width + Map.PlayRect.Height + 1;
	Rect bounds(0, 0, 1 << (subzone + 1), 1 << (subzone + 1));
	int X = 0;
	int Y = 0;
	while (subptr < subend) {
		int passability = zoneptr->Passability;
		int parent;
		if (subzone + 1 < SUBZONE_COUNT) {
			parent = subptr->SubzoneID[subzone + 1];
		} else {
			parent = 0;
		}

		if (passability == PASSABLE_OUTSIDE || subptr->SubzoneID[subzone] != 0) {
			subptr++;
			zoneptr++;
			X++;
		} else {
			LastAdjacentZone = 0;
			int count = Subzone_Span(subptr, subzone, entry_count, bounds, Cell(X, Y));

			track->Add(SubzoneTrackingStruct());

			SubzoneTrackingStruct * added = &(*track)[(unsigned short)entry_count];
			added->ParentSubzoneID = (unsigned short)parent;
			added->Passability = (PassabilityType)passability;
			added->Connections.Set_Growth_Step(16);
			added->ThreatRegion = Cell_Region(Cell(X, Y));

			entry_count++;
			subptr = &subptr[count];
			zoneptr = &zoneptr[count];
			X += count;
		}

		if (X == rowwidth) {
			Y++;
			X = 0;
			bounds.X = 0;
			bounds.Y = Y - (regionmask & Y);
		} else if ((X & regionmask) == 0) {
			bounds.X = X;
		}
	}

	SubzoneTrackingEntryCount[subzone] = (unsigned short)entry_count;

	Register_Subzone_Zone_Connections(subzone);

	for (int bucket_index = 0; bucket_index < 256; bucket_index++) {
		SUBZONE_CONNECTION_HASH_SET::BucketType & bucket = set->Buckets[bucket_index];
		if (bucket.Count() > 0) {
			SUBZONE_CONNECTION_HASH_SET::ObjectType * object = &bucket[0];
			for (int index = bucket.Count(); index > 0; index--) {
				unsigned packed = object->Value.SubzoneID;
				WORD low = LOWORD(packed);
				WORD high = HIWORD(packed);
				bool costly = object->Value.IsCrossBlock;

				SubzoneConnectionStruct conn(high);
				conn.IsCrossBlock = costly;
				(*track)[low].Connections.Add(conn);

				SubzoneConnectionStruct conn2(low);
				conn2.IsCrossBlock = costly;
				(*track)[high].Connections.Add(conn2);

				object++;
			}
		}
	}
}

// ---- helper types: the zone and subzone structures and the two hash-set typedefs are in ../helpers/zone.hh ----
