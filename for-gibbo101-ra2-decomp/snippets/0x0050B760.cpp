// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0050B760 (219 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xf4820 (VA 0x004F4820, 224 bytes incl. padding)
// RA2 symbol : ?Can_Build_Here@HouseClass@@QAE_NPAVBuildingTypeClass@@ABVCell@@@Z
// similarity : 0.9873 (very-similar, masked instruction tokens; shape 0.9693)
// source TU  : src/m85/src/house.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Can this house place a building at the specified location?
/// This routine keeps a computer base compact by requiring a candidate site to touch
/// something the house already occupies. Campaign games impose no such restriction.
/// </summary>
/// <param name="cell">The upper left cell of the proposed building location.</param>
/// <returns>bool; Is the location acceptable to build at?</returns>
bool HouseClass::Can_Build_Here(BuildingTypeClass *building, Cell const & cell)
{
	if (Session.Type == GAME_NORMAL) {
		return(true);
	}

	int spacing = Rule->AIBaseSpacing;
	int width = (2 * spacing) + building->Width();
	int height = (2 * spacing) + building->Height();

	int mask = 1 << HeapID;

	for (int x = cell.X - spacing - 1; x < cell.X + width + 1; x++) {
		for (int y = cell.Y - spacing - 1; y < cell.Y + height + 1; y++) {
			if (Map[Cell(x, y)].OccupiedBy & mask) {
				return(true);
			}
		}
	}

	return(false);
}
