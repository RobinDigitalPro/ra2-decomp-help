// ra2-decomp help snippet, update 2026-11-23 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00582D70 (1028 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0x161950 (VA 0x00561950, 1025 bytes without padding)
// RA2 symbol : ?Register_Zone_Connection_Entries@MapClass@@QAEXPAUZoneConnectionClass@@H@Z
// similarity : 0.9610 (very-similar, masked instruction tokens; shape 1.0000)
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

/// <summary>
/// Records the subzone links a bridge or tunnel makes at one subzone level.
/// A subzone rebuild only links cells that touch, so a span has to be stitched in by hand.
/// This routine stages the link between the two ends of the span and between the lanes either
/// side of them; the rebuild later unpacks the staged pairs into the subzone adjacency lists.
/// </summary>
/// <param name="connection">The bridge or tunnel connection to stitch in.</param>
/// <param name="index">The subzone level whose staging set receives the links.</param>
void MapClass::Register_Zone_Connection_Entries(ZoneConnectionClass * connection, int index) // RA2: 0x564B60, takes the connection by pointer
{
	SUBZONE_CONNECTION_HASH_SET::ObjectType connstr;
	SUBZONE_CONNECTION_HASH_SET * set = SubzoneConnectionHashTable[index];

	Cell from = connection->From; // RA2: as above
	Cell to = connection->To; // RA2: as above

	Cell enter1;
	Cell enter2;
	Cell newcell1;
	Cell newcell2;

	CellClass * cell1ptr = &Map[from];

	if (!cell1ptr->Is_Tile_Bridge() && !cell1ptr->Is_Tile_Train_Bridge()) {

		int enter_dir = cell1ptr->Get_Tunnel()->EnterDir; // RA2: the facing stays an int
		enter1 = Adjacent_Cell(from, (FacingType)(enter_dir + FACING_90)); // RA2: as above
		enter2 = from + AdjacentCell[(enter_dir - FACING_90) & 7]; // RA2: the cell table is indexed directly here

		CellClass * enterptr1 = &Map[enter1];
		TubeClass * tube1 = enterptr1->Get_Tunnel();
		CellClass * enterptr2 = &Map[enter2];
		TubeClass * tube2 = enterptr2->Get_Tunnel();

		if (tube1 == NULL || tube2 == NULL) {
			return;
		}

		int count1 = tube1->Count;
		newcell1 = Follow_Path(enter1, count1, tube1->Dirs);
		int count2 = tube2->Count;
		newcell2 = Follow_Path(enter2, count2, tube2->Dirs);
	} else {
		bool is_bridge = cell1ptr->Is_Tile_Bridge();
		IsometricTileType tile_set = IsometricTileTypeClass::BridgeSet;
		int tile;
		if (!is_bridge) {
			// level-2 1.001: STEERING: the same assignment in both arms (the 1.001 code keeps a copy in each arm; kind 1, AGENTS.md rule 9).
			tile = cell1ptr->ITType;
			tile_set = IsometricTileTypeClass::TrainBridgeSet;
		} else {
			tile = cell1ptr->ITType;
		}
		FacingType dir = BridgeSideFacings[tile - tile_set];

		enter1 = Adjacent_Cell(from, dir);
		enter2 = Adjacent_Cell(from, (FacingType)(dir - FACING_180)); // RA2: both second cells lie at dir - 4
		newcell1 = Adjacent_Cell(to, dir);
		newcell2 = Adjacent_Cell(to, (FacingType)(dir - FACING_180));
	}

	{
		int from_zone = CellSubzones[Get_Cell_Zone_Index(from)].SubzoneID[index];
		int to_zone = CellSubzones[Get_Cell_Zone_Index(to)].SubzoneID[index];

		int value = Zone_Pack32(from_zone, to_zone);
		Set_Zone_Record(connstr, value);
		set->Add_Object(Zone_Pack8(from_zone, to_zone), connstr);
	}

	{
		int from_zone = CellSubzones[Get_Cell_Zone_Index(enter1)].SubzoneID[index];
		int to_zone = CellSubzones[Get_Cell_Zone_Index(newcell1)].SubzoneID[index];

		int value = Zone_Pack32(from_zone, to_zone);
		Set_Zone_Record(connstr, value);
		set->Add_Object(Zone_Pack8(from_zone, to_zone), connstr);
	}

	{
		int from_zone = CellSubzones[Get_Cell_Zone_Index(enter2)].SubzoneID[index];
		int to_zone = CellSubzones[Get_Cell_Zone_Index(newcell2)].SubzoneID[index];

		int value = Zone_Pack32(from_zone, to_zone);
		Set_Zone_Record(connstr, value);
		set->Add_Object(Zone_Pack8(from_zone, to_zone), connstr);
	}
}
