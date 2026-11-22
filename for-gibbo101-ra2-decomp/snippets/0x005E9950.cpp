// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E9950 (105 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c3120 (VA 0x005C3120, 112 bytes incl. padding)
// RA2 symbol : ?Control_Slot@@YIHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9091)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __fastcall Control_Slot(int id) // RA2: 0x005C9800, not in TibSun; the slot a control belongs to, or -1
{
	if (id == 1041) { // RA2: as above
		return(0); // RA2: as above
	}
	if (id == 1042) { // RA2: as above
		return(1); // RA2: as above
	}
	if (id == 1043) { // RA2: as above
		return(2); // RA2: as above
	}
	if (id == 1044) { // RA2: as above
		return(3); // RA2: as above
	}
	if (id == 1045) { // RA2: as above
		return(4); // RA2: as above
	}
	if (id == 1046) { // RA2: as above
		return(5); // RA2: as above
	}
	if (id == 1047) { // RA2: as above
		return(6); // RA2: as above
	}
	return(id == 1048 ? 7 : -1); // RA2: as above
}
