// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005EAAD0 (96 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c3d60 (VA 0x005C3D60, 96 bytes incl. padding)
// RA2 symbol : ?Slot_Color_Control_Id@@YIHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __fastcall Slot_Color_Control_Id(int slot) // RA2: 0x005CA4E0, not in TibSun; the id of the control that shows a slot's color (1746 to 1753), or -1
{
	if (slot == 0) { // RA2: as above
		return(1746); // RA2: as above
	}
	if (slot == 1) { // RA2: as above
		return(1747); // RA2: as above
	}
	if (slot == 2) { // RA2: as above
		return(1748); // RA2: as above
	}
	if (slot == 3) { // RA2: as above
		return(1749); // RA2: as above
	}
	if (slot == 4) { // RA2: as above
		return(1750); // RA2: as above
	}
	if (slot == 5) { // RA2: as above
		return(1751); // RA2: as above
	}
	if (slot == 6) { // RA2: as above
		return(1752); // RA2: as above
	}
	return(slot == 7 ? 1753 : -1); // RA2: as above
}
