// ra2-decomp help snippet, update 2 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0058C800 (1678 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0x16aef0 (VA 0x0056AEF0, 1678 bytes without padding)
// RA2 symbol : ?Create_Region_From_Cell@MapRegionClass@@SIPAV1@PAVCellClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/mapgen.cpp
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
/// Creates a region grown out from a seed cell.
/// This routine gathers up every cell reachable from the seed that shares its height and
/// its wet or dry character, and makes a region of them. A dry patch too small to be
/// worth keeping is dissolved into its surroundings instead of becoming a region, and
/// the ground under it is flattened to match.
/// </summary>
/// <param name="cptr">The cell to grow the region out from.</param>
/// <returns>Returns with the region created. NULL is returned when the patch was
/// dissolved rather than kept.</returns>
MapRegionClass *MapRegionClass::Create_Region_From_Cell(CellClass *cptr) // RA2: RA2's form (0x56E100): green-LAT ground counts as water-like and the wipes call Clear_Region_Cells; level-2 1.001: 0x56AEF0
{
	int i;
	int region_id = MapRegionClass::TotalCount;

	DynamicVectorClass<Cell> cells;
	cells.Set_Growth_Step(50000);
	cells.Add(cptr->Fetch_CellID());

	bool has_water = cptr->Is_Tile_With_Water() || cptr->Is_Tile_Clear_To_Green_LAT(); // RA2: as above
	int cell_height = cptr->Height;
	int processed_count = 0;

	int pending = cells.Count();
	while (pending) {
		Cell cell = cells[pending - 1];
		cells.Delete_Index(pending - 1);

		CellData::Set_Spread(cell, region_id);
		CellData::Set_Region(cell, region_id);

		Cell ncell;
		for (i = 0; i < FACING_COUNT; i++) {
			ncell = Adjacent_Cell(cell, (FacingType)i);
			CellData & ndata = MapRegionClass::Get_Cell_Data(ncell);
			if (My_In_Radar(ncell)) {
				if (ndata.RegionID == -1 && ndata.SpreadID != region_id) {
					ndata.SpreadID = region_id;
					if (Map[ncell].Height == cell_height) {
						int n_has_water = Map[ncell].Is_Tile_With_Water() || Map[ncell].Is_Tile_Clear_To_Green_LAT(); // RA2: as above
						if (!(has_water ^ n_has_water)) {
							cells.Add(ncell);
						}
					}
				}
			}
		}

		processed_count++;
		pending = cells.Count();
	}

	if (processed_count < 75 && !has_water) {
		bool reset_done = false;

		if (region_id == 0) {
			DynamicVectorClass<Cell> * region_cells = RandomMapGen.Build_Region_Border_Cell_List(0);
			Cell region_cell = (*region_cells)[Pick_Random_UInt(0, region_cells->Count() - 1)];

			Cell ncell;
			for (i = 0; i < FACING_COUNT; i++) {
				ncell = Adjacent_Cell(region_cell, (FacingType)i);
				if (My_In_Radar(ncell)) {
					if (Map[ncell].Height != Map[region_cell].Height && !Map[ncell].Is_Tile_With_Water()) {
						int height = Map[ncell].Height;

						RandomMapGen.Clear_Region_Cells(0, -1, height, 0); // RA2: as above

						reset_done = true;
						break;
					}
				}
			}

			delete region_cells;
		} else {
			Cell side_cell = cptr->Fetch_CellID() - Cell(1, 0); // level-2 1.001: offsets from the fetched cell (exe temporaries at 0x56B390)
			if (!Is_Region_Side_In_Radar(side_cell)) {
				side_cell = cptr->Fetch_CellID() - Cell(0, 1);
			}

			if (My_In_Radar(side_cell)) {
				int id = CellData::Get_Region(side_cell);
				int height = Map[side_cell].Height;

				RandomMapGen.Clear_Region_Cells(region_id, id, height, 0); // RA2: as above

				reset_done = true;
			}
		}

		if (reset_done) {
			return(NULL);
		}
	}

	MapRegionClass * region = Create_Seed_Region(cptr, cell_height, has_water);
	region->Recount_Cells();
	return(region);
}
