// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00638B70 (167 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20d4f0 (VA 0x0060D4F0, 176 bytes incl. padding)
// RA2 symbol : ?Planning_Order_Stays_Put@@YI_NPAVTechnoClass@@HVTargetClass@@@Z
// similarity : 0.9500 (very-similar, masked instruction tokens; shape 0.9302)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Planning_Order_Stays_Put(TechnoClass * techno, int mission, TargetClass target) // RA2: 0x00615910; an area guard order that aims at nothing, or at the cell the techno stands on already
{
	if (mission == 11) { // RA2: as above
		if (!target.Is_Valid()) { // RA2: as above
			return true; // RA2: as above
		}
		if (techno) { // RA2: as above
			Cell here = techno->Get_Cell(); // RA2: as above
			Cell cell = techno->Get_Cell(); // RA2: as above
			CellClass * target_cell = target.As_Cell(); // RA2: as above
			if (target_cell) { // RA2: as above
				cell = target_cell->CellID; // RA2: as above
			} else { // RA2: as above
				TechnoClass * target_techno = target.As_Techno(); // RA2: as above
				if (target_techno) { // RA2: as above
					cell = target_techno->Get_Cell(); // RA2: as above
				}
			}
			if (here == cell) { // RA2: as above
				return true; // RA2: as above
			}
		}
	}
	return false; // RA2: as above
}
