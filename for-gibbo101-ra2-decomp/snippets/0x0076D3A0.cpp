// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0076D3A0 (193 bytes; gibbo status: attempted-partial 65.3%)
// RA2 RVA    : 0x323210 (VA 0x00723210, 208 bytes incl. padding)
// RA2 symbol : ?Select_Territory_At@Selection@WorldDominationTour@@QAE_NABVPoint2D@@@Z
// similarity : 0.9608 (very-similar, masked instruction tokens; shape 0.8718)
// source TU  : src/m85/src/wdtsel.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool Selection::Select_Territory_At(Point2D const & point) // RA2: refreshes the hovered territory, then selects it
{
	Update_Hovered_Territory(point);
	rc_ptr<Territory> territory = true ? WorldMap->Get_Territory(HoveredTerritoryID) : rc_ptr<Territory>(); // RA2: the dead condition is in the executable: a zeroed flag for the temporary and the copy through the default constructor and Set
	return(Select_Territory(territory));
}
