// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00635680 (324 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20a000 (VA 0x0060A000, 336 bytes incl. padding)
// RA2 symbol : ?Frame_Lead_Box_Outer@PlanningNodeClass@@QAEXH@Z
// similarity : 0.9804 (very-similar, masked instruction tokens; shape 0.9444)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void PlanningNodeClass::Frame_Lead_Box_Outer(int color) // RA2: 0x00612420
{
	Rect clip = Get_Title_Screen_Area(); // RA2: as above
	Rect rect = Lead_Box_Rect2(); // RA2: as above
	for (int i = 0; i < 3; i++) { // RA2: as above
		CompositeSurface->Draw_Rect(clip, rect, color); // RA2: as above
		Shrink_Rect(rect); // RA2: as above; level-2 1.001: the shrink helper
	}
}
