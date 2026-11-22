// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00487C80 (7 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x7ca40 (VA 0x0047CA40, 16 bytes incl. padding)
// RA2 symbol : ?Get_Rad_Site@CellClass@@QAEPAVRadSiteClass@@XZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.3077)
// source TU  : src/m85/src/cell.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

RadSiteClass * CellClass::Get_Rad_Site(void) // RA2: not in TibSun, at 0x47CE40
{
	return(RadSite);
}
