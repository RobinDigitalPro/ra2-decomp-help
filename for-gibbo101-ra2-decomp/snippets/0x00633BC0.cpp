// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00633BC0 (150 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x208560 (VA 0x00608560, 160 bytes incl. padding)
// RA2 symbol : ?Planning_Event_Coord@@YI?AVCoord@@ABVEventClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9254)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

Coord __fastcall Planning_Event_Coord(EventClass const & event) // RA2: 0x00610980; where the order of a mission event points (target, destination or follow), (-1, -1, -1) for none
{
	if (event.Type == EventClass::MEGAMISSION) { // RA2: as above
		AbstractClass * object; // RA2: as above
		if (event.Data.MegaMission.Target.Is_Valid()) { // RA2: as above
			object = event.Data.MegaMission.Target.As_Abstract(); // RA2: as above
			if (object) { // RA2: as above
				return object->As_Coord(); // RA2: as above
			}
		} else if (event.Data.MegaMission.Follow.Is_Valid()) { // RA2: as above
			object = event.Data.MegaMission.Follow.As_Abstract(); // RA2: as above
			if (object) { // RA2: as above
				return object->As_Coord(); // RA2: as above
			}
		} else if (event.Data.MegaMission.Destination.Is_Valid()) { // RA2: as above
			object = event.Data.MegaMission.Destination.As_Abstract(); // RA2: as above
			if (object) { // RA2: as above
				return object->As_Coord(); // RA2: as above
			}
		}
	}
	return Coord(-1, -1, -1); // RA2: as above
}
