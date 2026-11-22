// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063CA80 (87 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2113f0 (VA 0x006113F0, 96 bytes incl. padding)
// RA2 symbol : ?Planning_Event_Or_Object_Coord@@YI?AVCoord@@ABVEventClass@@PAVAbstractClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8889)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

Coord __fastcall Planning_Event_Or_Object_Coord(EventClass const & event, AbstractClass * object) // RA2: 0x00619810; where the order of an event points, or where the object is when it points nowhere
{
	Coord coord = Planning_Event_Coord(event); // RA2: as above
	if (coord == Coord(-1, -1, -1) && object != NULL) { // RA2: as above
		coord = object->As_Coord(); // RA2: as above
	}
	return coord; // RA2: as above
}
