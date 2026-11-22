// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007691E0 (196 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31f0d0 (VA 0x0071F0D0, 208 bytes incl. padding)
// RA2 symbol : ?Get_Drawer@Map@WorldDominationTour@@QAEPAVConvertClass@@ABVWstring@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9277)
// source TU  : src/m85/src/wdtmap.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

ConvertClass * Map::Get_Drawer(Wstring const & name) // RA2: the drawer of a palette file, loaded and kept on first use. Out of line at both call sites
{
	for (int i = 0; i < Palettes.Count(); i++) { // RA2: as above
		if (Palettes[i]->Name == name) { // RA2: as above
			return Palettes[i]->Drawer; // RA2: as above
		}
	}
	ConvertClass * drawer = Create_Drawer(name); // RA2: as above
	if (drawer) { // RA2: as above
		Palettes.Add(new AnimationPalette(name, drawer)); // RA2: as above
	}
	return drawer; // RA2: as above
}
