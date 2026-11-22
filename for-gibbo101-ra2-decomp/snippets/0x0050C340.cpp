// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0050C340 (1399 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xf5230 (VA 0x004F5230, 1408 bytes incl. padding)
// RA2 symbol : ?Add_Wall_Nodes@HouseClass@@QAE_NH@Z
// similarity : 0.9770 (very-similar, masked instruction tokens; shape 0.9907)
// source TU  : src/m85/src/house.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool HouseClass::Add_Wall_Nodes(int node) // RA2: RA2's form
{
	int wall = -1; // RA2: as above
	for (int wi = 0; wi < Rule->ConcreteWalls.Count(); wi++) { // RA2: as above
		if (Rule->ConcreteWalls[wi]->AIBasePlanningSide == Class->Side || Rule->ConcreteWalls[wi]->AIBasePlanningSide == -1) { // RA2: as above
			wall = Rule->ConcreteWalls[wi]->HeapID; // RA2: as above
			break;
		}
	}

	BuildingClass * building = NULL; // RA2: as above
	int index;
	for (index = node - 1; index >= 0; index--) { // RA2: as above
		building = Base.Get_Building(index); // RA2: as above
		if (building != NULL && building->Class->ProtectWithWall && Base.Nodes[index + 1].Type != wall) { // RA2: as above
			break;
		}
	}

	if (index == -1 || building == NULL || !building->Class->ProtectWithWall) { // RA2: as above
		return(false);
	}

#ifdef LEVEL2_BASENODE_1001
	/*
	**	level-2 1.001: the cell comes through the inline As_Cell, and the nodes are inserted with the
	**	Insert_After(object, index) overload (out of line at 0x4f6770 for the last corners) and the
	**	BaseNodeClass(StructType, Cell const &) constructor (0x4f60e0). Both need the header changes
	**	that define LEVEL2_BASENODE_1001 (vector.h, base.h).
	*/
	Coord coord = building->Get_Coord(); // level-2 1.001
	Cell cell = coord.As_Cell(); // level-2 1.001
	BuildingTypeClass const * type = building->Class; // RA2: as above
	int width = type->Width(); // RA2: as above
	int height = type->Height(false); // RA2: as above
	Cell corner = cell - Cell(1, 1); // RA2: as above

	for (node = 1; node <= width; node++) { // RA2: as above
		Base.Nodes.Insert_After(BaseNodeClass((StructType)wall, corner + Cell(node, 0)), index); // level-2 1.001
		Base.Nodes.Insert_After(BaseNodeClass((StructType)wall, corner + Cell(node, height + 1)), index); // level-2 1.001
	}
	for (node = 1; node <= height; node++) { // RA2: as above
		Base.Nodes.Insert_After(BaseNodeClass((StructType)wall, corner + Cell(0, node)), index); // level-2 1.001
		Base.Nodes.Insert_After(BaseNodeClass((StructType)wall, corner + Cell(width + 1, node)), index); // level-2 1.001
	}

	Base.Nodes.Insert_After(BaseNodeClass((StructType)wall, corner + Cell(0, 0)), index); // level-2 1.001
	Base.Nodes.Insert_After(BaseNodeClass((StructType)wall, corner + Cell(width + 1, 0)), index); // level-2 1.001
	Base.Nodes.Insert_After(BaseNodeClass((StructType)wall, corner + Cell(0, height + 1)), index); // level-2 1.001
	Base.Nodes.Insert_After(BaseNodeClass((StructType)wall, corner + Cell(width + 1, height + 1)), index); // level-2 1.001
	return(true);
#else
	Coord coord = building->PositionCoord; // RA2: as above
	Cell cell(coord.X / 256, coord.Y / 256); // RA2: as above
	BuildingTypeClass const * type = building->Class; // RA2: as above
	int width = type->Width(); // RA2: as above
	int height = type->Height(false); // RA2: as above
	Cell corner = cell - Cell(1, 1); // RA2: as above

	for (node = 1; node <= width; node++) { // RA2: as above
		Base.Nodes.Insert_After(index, BaseNodeClass((StructType)wall, corner + Cell(node, 0))); // RA2: as above
		Base.Nodes.Insert_After(index, BaseNodeClass((StructType)wall, corner + Cell(node, height + 1))); // RA2: as above
	}
	for (node = 1; node <= height; node++) { // RA2: as above
		Base.Nodes.Insert_After(index, BaseNodeClass((StructType)wall, corner + Cell(0, node))); // RA2: as above
		Base.Nodes.Insert_After(index, BaseNodeClass((StructType)wall, corner + Cell(width + 1, node))); // RA2: as above
	}

	Base.Nodes.Insert_After(index, BaseNodeClass((StructType)wall, corner + Cell(0, 0))); // RA2: as above
	Base.Nodes.Insert_After(index, BaseNodeClass((StructType)wall, corner + Cell(width + 1, 0))); // RA2: as above
	Base.Nodes.Insert_After(index, BaseNodeClass((StructType)wall, corner + Cell(0, height + 1))); // RA2: as above
	Base.Nodes.Insert_After(index, BaseNodeClass((StructType)wall, corner + Cell(width + 1, height + 1))); // RA2: as above
	return(true);
#endif
}
