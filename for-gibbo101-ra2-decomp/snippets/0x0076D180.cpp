// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0076D180 (532 bytes; gibbo status: attempted-partial 100.0%)
// RA2 RVA    : 0x322ff0 (VA 0x00722FF0, 544 bytes incl. padding)
// RA2 symbol : ?Handle_Click@Selection@WorldDominationTour@@QAEXABVPoint2D@@AA_N@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9623)
// source TU  : src/m85/src/wdtsel.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Selection::Handle_Click(Point2D const & point, bool & selected) // RA2: a press on the back button or on the map
{
	switch (Region_At(point)) { // RA2: the back button region and state of the map (an exact copy of the executable)
		case 2:
			WorldMap->Set_Back_Hot(this, true); // RA2: the back button region and state of the map (an exact copy of the executable)
			On_Cancel_Enter();
			break;

		case 1:
			WorldMap->Set_Back_Hot(this, false); // RA2: the back button region and state of the map (an exact copy of the executable)
			selected = Hover_At(point); // RA2: as above
			if (selected) {
				Play_SFX("ConflictSelected");
			}
			break;
	}
}
