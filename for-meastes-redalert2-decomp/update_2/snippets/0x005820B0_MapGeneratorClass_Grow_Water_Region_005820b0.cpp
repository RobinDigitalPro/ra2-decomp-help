// RA2 1.001 byte-identical (VC6 8168 /O2 /Ob2 /Gr /GR /Gy), RVA 0x17eeb0, from our src/m85/src/mapgen.cpp. GPL-3.0-or-later.
// Your 1.006 entry 0x005820B0 (MapGeneratorClass::Grow_Water_Region_005820b0, 2230 bytes, non_exact in your map).

bool MapGeneratorClass::Grow_Water_Region(int region_id, float spread_scale, Rect const & bounds, Cell const & origin, bool claim_frontier) // level-2 1.001: RVA 0x17eeb0
{
	CellNode * nodes = new CellNode[MAX(2 * LocalHeight * LocalWidth, 100)];
	PriorityQueueClass<CellNode> * queue = new PriorityQueueClass<CellNode>(MAX(2 * LocalHeight * LocalWidth, 100));

	int marker_index = 0;
	bool result_flag = true;

	double angle = 0.0;
	if (bounds.X != 0) {
		angle = 0.0;
	} else if (bounds.Width != MAP_CELL_W) {
		angle = M_PI;
	}
	if (bounds.Y != 0) {
		angle = 3 * M_PI_2;
	} else if (bounds.Height != MAP_CELL_H) {
		angle = M_PI_2;
	}

	Clear_Cell_Data_Spreads();

	DynamicVectorClass<Cell> * seed_cells = Build_Region_Border_Cell_List(region_id);
	int seed_count = seed_cells->Count();

	for (int seed_index = 0; seed_index < seed_count; seed_index++) {
		Cell seed = (*seed_cells)[seed_index];
		if (bounds.Is_Point_Within(Point2D(seed.X, seed.Y))) {

			nodes[marker_index].Element = seed;
			nodes[marker_index].Score = Get_Angle_Score(origin, seed, angle);
			queue->Insert(nodes[marker_index++]);
		}
	}

	delete seed_cells;

	double scale = log((double)seed_count);
	scale = max(1.0, scale);

	int spread_count = (int)(1.0f / ((float)(1.0 / scale) * spread_scale) * 0.5f);
	spread_count += Pick_Random_UInt(0, spread_count / 2);

	CellNode * node = queue->Extract_Min();

	int spread_step = 0;
	while (spread_step < spread_count && result_flag && node != NULL) {

		MapRegionClass::CellData & ndata = MapRegionClass::Get_Cell_Data(node->Element);
		if (!ndata.RegionID) {
			if (Map[node->Element].Is_Tile_Clear()) {
				ndata.CanExpand = true;
				ndata.RegionID = region_id;
			}
		}

		for (FacingType dir = FACING_FIRST; dir < FACING_COUNT; dir = FacingType(dir + FACING_90)) {
			Cell newcell = Adjacent_Cell(node->Element, dir);
			if (My_In_Radar(newcell)) {
				if (MapRegionClass::CellData::Get_Region(newcell) == 0 &&
					MapRegionClass::Get_Cell_Data(newcell).SpreadID != region_id &&
					bounds.Is_Point_Within(Point2D(newcell.X, newcell.Y)) &&
					Map[newcell].Is_Tile_Clear()) {
					nodes[marker_index].Element = newcell;
					nodes[marker_index].Score = Get_Angle_Score(origin, newcell, angle);
					Set_Cell_Data_Spread(newcell, region_id);
					queue->Insert(nodes[marker_index++]);
				} else {
					if (MapRegionClass::CellData::Get_Region(newcell) != 0 && MapRegionClass::CellData::Get_Region(newcell) != region_id) {
						result_flag = false;
					}
				}
			}
		}

		spread_step++;
		angle += Sample_Normal(0, M_PI_4);
		node = queue->Extract_Min();
	}

	if (claim_frontier) {
		for (CellNode * remaining = queue->Extract_Min(); remaining != NULL && result_flag; remaining = queue->Extract_Min()) {

			Claim_Water_Cell(remaining->Element, region_id, result_flag);

		}
	}

	delete[] nodes;
	Delete_Water_Queue(queue);

	return(result_flag);
}
