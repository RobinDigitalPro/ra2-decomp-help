// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00638C70 (98 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20d5f0 (VA 0x0060D5F0, 112 bytes incl. padding)
// RA2 symbol : ?Planning_Mission_Allows@@YI_NPAVTechnoClass@@@Z
// similarity : 0.9535 (very-similar, masked instruction tokens; shape 0.8600)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Planning_Mission_Allows(TechnoClass * techno) // RA2: 0x00615A10; whether the current mission of a techno lets planning mode take over: guarding, or attacking or guarding an area with a cell or (for the area) nothing as the target
{
	if (techno) { // RA2: as above
		int mission = techno->Get_Mission(); // RA2: as above
		if (mission == 5) { // RA2: as above
			return true; // RA2: as above
		}
		return Planning_Target_Fits(mission, TargetClass(techno->TarCom)); // RA2: as above
	}
	return false; // RA2: as above
}
