// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0050C050 (76 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xf4f20 (VA 0x004F4F20, 80 bytes incl. padding)
// RA2 symbol : ?Speed_Multiplier@HouseClass@@QBEMPBVTechnoTypeClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9286)
// source TU  : src/m85/src/house.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

float HouseClass::Speed_Multiplier(TechnoTypeClass const * type) const // RA2: RA2's form
{
	switch (type->Fetch_RTTI()) { // RA2: as above
		case RTTI_INFANTRYTYPE:
			return(Class->SpeedInfantryMult); // RA2: as above
		case RTTI_UNITTYPE:
			return(Class->SpeedUnitsMult); // RA2: as above
		case RTTI_AIRCRAFTTYPE:
			return(Class->SpeedAircraftMult); // RA2: as above
	}
	return(1.0f); // RA2: as above
}
