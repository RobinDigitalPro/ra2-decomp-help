// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063D210 (184 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x211b80 (VA 0x00611B80, 192 bytes incl. padding)
// RA2 symbol : ?Planning_Event_Pixel@@YI?AVPoint2D@@PBVEventClass@@PAVAbstractClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9394)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

Point2D __fastcall Planning_Event_Pixel(EventClass const * event, AbstractClass * object) // RA2: 0x00619FA0; the pixel an order points at, or where the object is when it points nowhere; (-1, -1) for no order
{
	Point2D pixel(-1, -1); // RA2: as above
	if (event != NULL) { // RA2: as above
		EventClass copy = *event; // RA2: as above
		Coord coord = Planning_Event_Or_Object_Coord(copy, object); // RA2: as above
		pixel = Planning_Coord_Pixel(coord); // RA2: as above
	}
	return pixel; // RA2: as above
}
