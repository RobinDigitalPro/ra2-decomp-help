// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E98F0 (96 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c30c0 (VA 0x005C30C0, 96 bytes incl. padding)
// RA2 symbol : ?Get_Slot_Control_Id@@YIHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __fastcall Get_Slot_Control_Id(int slot) // RA2: 0x005C97A0, the id of the control of a slot (1041 to 1048, not in TibSun's resource list), or -1; the callers before it expand it inline
{
	if (slot == 0) { // RA2: as above
		return(1041); // RA2: as above
	}
	if (slot == 1) { // RA2: as above
		return(1042); // RA2: as above
	}
	if (slot == 2) { // RA2: as above
		return(1043); // RA2: as above
	}
	if (slot == 3) { // RA2: as above
		return(1044); // RA2: as above
	}
	if (slot == 4) { // RA2: as above
		return(1045); // RA2: as above
	}
	if (slot == 5) { // RA2: as above
		return(1046); // RA2: as above
	}
	if (slot == 6) { // RA2: as above
		return(1047); // RA2: as above
	}
	return(slot == 7 ? 1048 : -1); // RA2: as above
}
