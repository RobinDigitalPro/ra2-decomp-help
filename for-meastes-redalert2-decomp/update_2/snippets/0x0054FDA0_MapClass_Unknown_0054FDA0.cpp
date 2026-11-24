// RA2 1.001 byte-identical (VC6 8168 /O2 /Ob2 /Gr /GR /Gy), RVA 0x14d230, from our src/m85/src/map.cpp. GPL-3.0-or-later.
// Your 1.006 entry 0x0054FDA0 (MapClass::Unknown_0054FDA0, 804 bytes, non_exact in your map).

void MapClass::Compute_Zone_Connections(void)
{
	static int _bridge_subtiles1[] = {
		7, 7, -1, 7, 7, -1, 4, 4,
		4, 4,  4, 2, 2,  2, 2, 2
	};
	static FacingType _facings[] = {
		FACING_E, FACING_E, FACING_NONE, FACING_S, FACING_S, FACING_NONE, FACING_E, FACING_E,
		FACING_E, FACING_E,    FACING_E, FACING_S, FACING_S,    FACING_S, FACING_S, FACING_S
	};
	static int _bridge_subtiles2[] = {
		-1, -1, 4, -1, -1, 2, 4, 4,
		 4,  4, 4,  2,  2, 2, 2, 2
	};

	ZoneConnections.Clear();
	Reset_Iterator();
	CellClass * cptr = Iterate();

	while (cptr != NULL) {

		if (!cptr->Is_Tile_Bridge() && !cptr->Is_Tile_Train_Bridge()) {

			/*
			 * A tunnel entrance pairs with its exit cell; record the connection once,
			 * from the lower numbered cell of the pair.
			 */
			if (cptr->Has_Tunnel()) {
				if ((cptr->Adjacent_Cell(FACING_E).Has_Tunnel() && cptr->Adjacent_Cell(FACING_W).Has_Tunnel()) ||
					(cptr->Adjacent_Cell(FACING_S).Has_Tunnel() && cptr->Adjacent_Cell(FACING_N).Has_Tunnel())) {

					Cell cell = cptr->Get_Tunnel()->Exit;
					int from_index = Map_Cell_Index(cptr->CellID);
					int to_index = Map_Cell_Index(cell);
					if (from_index == max(to_index, from_index)) { // level-2 1.001: STEERING select the higher endpoint to keep the first index in EBX.
						cptr = Iterate(); // level-2 1.001: STEERING advance on the skip path to share the outer iterator reload.
						continue;
					}

					Cell exit = cptr->Get_Tunnel()->Exit;
					ZoneConnectionClass con;
					con.From = cptr->CellID;
					con.To = exit;
					con.IsPassable = true;
					con.Type = 1;
					ZoneConnections.Add(con);
				}
			}

		} else {

			int faceindex;
			if (cptr->Is_Tile_Bridge()) {
				faceindex = cptr->ITType - IsometricTileTypeClass::BridgeSet;
			} else {
				faceindex = cptr->ITType - IsometricTileTypeClass::TrainBridgeSet;
			}

			/*
			 * Only walk the span from its starting subtile.
			 */
			if (_bridge_subtiles1[faceindex] == cptr->SubTile) {

				FacingType facing = _facings[faceindex];
				bool crossed = false;
				bool passable = true;

				/*
				 * Walk across the span until the far end subtile has been passed or
				 * the walk leaves the radar map.
				 */
				for (CellClass * bptr = &cptr->Adjacent_Cell(facing); ; bptr = &bptr->Adjacent_Cell(facing)) {

					if (In_Radar(bptr->CellID)) {

						if (!crossed) {

							int index = -1;
							if (bptr->Is_Tile_Bridge()) {
								index = bptr->ITType - IsometricTileTypeClass::BridgeSet;
							} else if (bptr->Is_Tile_Train_Bridge()) {
								index = bptr->ITType - IsometricTileTypeClass::TrainBridgeSet;
							} else {
								if (!bptr->IsUnderBridge) {
									passable = false;
								}
							}
							if (index != -1 && _bridge_subtiles2[index] == bptr->SubTile) {
								crossed = true;
							}
							continue;
						}

					} else if (!crossed) {
						break;
					}

					/*
					 * Record the bridge span as a zone connection.
					 */
					Cell exit = bptr->Adjacent_Cell((FacingType)((facing - FACING_180) & 7)).CellID;
					ZoneConnectionClass con;
					con.From = cptr->CellID;
					con.To = exit;
					con.IsPassable = passable;
					con.Type = 0;
					ZoneConnections.Add(con);
					break;
				}
			}
		}

		cptr = Iterate();
	}
}
