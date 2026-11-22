// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0059BBC0 (2415 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x17a1a0 (VA 0x0057A1A0, 2416 bytes incl. padding)
// RA2 symbol : ?Spread_Land@MapGeneratorClass@@QAEHHABV?$TRect@H@@ABVPoint2D@@_NABVCell@@N2@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9993)
// source TU  : src/m85/src/mapgen.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: grows a patch of land (clear tiles in the water) of about count cells as a priority-queue flood fill from
/// the seed point, or from a random clear unclaimed cell when the seed is (0,0). Candidate cells are scored by their
/// distance from a point that wanders off by a normal sample of the wander scale every step -- or, when weighted,
/// by Direction_Weighted_Cell_Distance -- so the patch comes out ragged. The cells taken become the working region;
/// the region's shores are then built. If the shores cannot be built, the region is flooded again.
/// </summary>
/// <returns>The number of cells taken, or 0 when no seed was found or the region was flooded again.</returns>
int MapGeneratorClass::Spread_Land(int count, Rect const & bounds, Point2D const & seed, bool shaped, Cell const & center, double wander, bool weighted) // level-2 1.001: gibbo101's form (0x57A1A0)
{
	static const double _random_range = 5.0; // level-2 1.001: a static constant (0x790D20), not the shared literal

	count = MAX(count, 400);
	int heap_size = MAX(count * 8 + 2, 100);
	CellNode * nodes = new CellNode[heap_size];
	PriorityQueueClass<CellNode> * queue = new PriorityQueueClass<CellNode>(heap_size);
	Cell start;
	if (seed.X == 0 && seed.Y == 0) {
		int tries = 0;
		do {
			unsigned int x = Pick_Random_UInt(0, Map.PlayRect.Width - 1);
			unsigned int y = Pick_Random_UInt(0, Map.PlayRect.Height - 1);
			Cell first_offset = Cell(1, Map.PlayRect.Width) + Cell(x, -x);
			start = first_offset + Cell(y, y);
		} while (++tries < 200 && !(MapRegionClass::CellData::Get_Region(start) == 0 && Map[start].Is_Tile_With_Water()));
		if (tries >= 200) return 0;
	} else {
		start = Cell(seed.X, seed.Y);
	}

	float weight_x = 0.0f;
	float weight_y = 0.0f;
	if (!(bounds == RECT_NONE)) {
		int width = bounds.Width;
		int height = bounds.Height;
		if (width > height) {
			weight_x = 1.0f;
			weight_y = (double)width / height * 1.2;
		} else {
			weight_x = (double)height / width * 1.2;
			weight_y = 1.0f;
		}
	}

	double wander_x = start.X;
	double wander_y = start.Y;
	int spread_count = 0;
	queue->Clear();
	int used = 1;
	nodes[0].Element = start;
	nodes[0].Score = 0.0f;
	MapRegionClass::CellData::Set_Spread(start, WorkingRegionID);
	queue->Insert(nodes[0]);
	CellNode * node = queue->Extract_Min();
	double scale_x = 1.0 / ((bounds.Width * 0.5) * (bounds.Width * 0.5));
	double scale_y = 1.0 / ((bounds.Height * 0.5) * (bounds.Height * 0.5));
	while (spread_count < count) {
		if (node == NULL) break;
		MapRegionClass::CellData::Set_Region(node->Element, WorkingRegionID);
		Map[node->Element].ITType = ISOTILE_CLEAR;
		int facing = FACING_FIRST;
		for (; facing < FACING_COUNT; facing += FACING_90) {
			Cell adjacent = node->Element + AdjacentCell[facing & 7];
			if (My_In_Radar(adjacent)) {
				MapRegionClass::CellData & data = MapRegionClass::Get_Cell_Data(adjacent);
				if (data.RegionID == 0 && data.SpreadID != WorkingRegionID &&
					Map[adjacent].Is_Tile_With_Water() && used < heap_size &&
					Cell_In_Generation_Shape(adjacent, bounds, shaped, scale_x, scale_y)) {
					nodes[used].Element = adjacent;
					Cell wander_cell = Cell((int)(wander_x + 0.5), (int)(wander_y + 0.5));
					if (weighted) {
						nodes[used].Score = Direction_Weighted_Cell_Distance(wander_cell, adjacent, bounds, center, weight_x, weight_y);
					} else {
						double distance = Map_Cell_Distance(adjacent, wander_cell);
						nodes[used].Score = distance + RMG_RANDOM_DOUBLE(_random_range);
					}
					data.SpreadID = WorkingRegionID;
					queue->Insert(nodes[used++]);
				}
			}
		}
		wander_x += RMGGaussian() * wander;
		wander_y += RMGGaussian() * wander;
		++spread_count;
		node = queue->Extract_Min();
	}

	CellNode * remaining = queue->Extract_Min();
	while (remaining != NULL) {
		CellClass * current = &Map[remaining->Element];
		MapRegionClass::CellData & data = MapRegionClass::Get_Cell_Data(remaining->Element);
		if (data.RegionID == 0 && current->Is_Tile_With_Water()) {
			current->ITType = ISOTILE_CLEAR;
			data.RegionID = WorkingRegionID;
		}
		remaining = queue->Extract_Min();
		++spread_count;
	}
	delete[] nodes;
	delete queue;
	bool success = Map.Build_All_Shores(WorkingRegionID, true);
	Clear_Shore_Tiles();
	int result;
	if (!success) {
		Clear_Region_Cells(WorkingRegionID, 0, -1, IsometricTileTypeClass::WaterSet);
		result = 0;
	} else {
		result = spread_count;
		WorkingRegionID++;
	}
	return result;
}
