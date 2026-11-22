// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00455820 (344 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x50240 (VA 0x00450240, 352 bytes incl. padding)
// RA2 symbol : ?DisguiseDetectorActivate@BuildingClass@@UAEXVCell@@@Z
// similarity : 0.9550 (very-similar, masked instruction tokens; shape 0.9652)
// source TU  : src/m85/src/building.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Turns on a disguise detector: the cells within its SensorsSight are sensed by the owner,
/// and the units, infantry and aircraft standing in them are told they were sensed.
/// </summary>
/// <param name="cell">The cell to center on; CELL_NONE means the building's own cell.</param>
void BuildingClass::DisguiseDetectorActivate(Cell cell) // RA2: not in TibSun, at 0x450550
{
	if (!IsPowerOnline()) {
		return;
	}

	int radius = Class->SensorsSight;
	int dist = radius * radius;
	HousesType houseid = House->HeapID;
	if (cell == CELL_NONE) {
		cell = Center_Coord().As_Cell();
	}
	for (int y = -radius; y < radius; y++) {
		for (int x = -radius; x < radius; x++) {
			Cell newcell = Cell(cell.X + x, cell.Y + y);
			if (x * x + y * y < dist) {
				CellClass * cellptr = &Map[newcell];
				cellptr->Sensed_By(houseid); // RA2: Sensed_By, where the deactivation calls Disguise_Unsensed_By
				for (ObjectClass * occupier = cellptr->Cell_Occupier(); occupier != NULL; occupier = occupier->Next) {
					RTTIType rtti = occupier->RTTI;
					if (rtti == RTTI_UNIT || rtti == RTTI_INFANTRY || rtti == RTTI_AIRCRAFT) {
						((TechnoClass *)occupier)->Try_To_Cloak();
					}
				}
			}
		}
	}
}
