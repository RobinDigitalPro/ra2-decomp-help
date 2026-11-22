// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063B050 (48 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20f9d0 (VA 0x0060F9D0, 48 bytes incl. padding)
// RA2 symbol : ?First_Target_Object@PlanningFirstTarget@@QBEPAVAbstractClass@@XZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

AbstractClass * PlanningFirstTarget::First_Target_Object(void) const // RA2: 0x00617DF0
{
	AbstractClass * object = NULL; // RA2: as above
	if (Data.MegaMission.Target.Is_Valid()) { // RA2: as above
		object = Data.MegaMission.Target.As_Abstract(); // RA2: as above
	} else if (Data.MegaMission.Follow.Is_Valid()) { // RA2: as above
		object = Data.MegaMission.Follow.As_Abstract(); // RA2: as above
	} else if (Data.MegaMission.Destination.Is_Valid()) { // RA2: as above
		object = Data.MegaMission.Destination.As_Abstract(); // RA2: as above
	}
	return object; // RA2: as above
}
