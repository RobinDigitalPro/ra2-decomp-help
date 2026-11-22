// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004C29E0 (115 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xb20c0 (VA 0x004B20C0, 128 bytes incl. padding)
// RA2 symbol : ?Delete_All@EBolt@@SAXXZ
// similarity : 0.9737 (very-similar, masked instruction tokens; shape 0.8539)
// source TU  : src/m85/src/ebolt.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Deletes every bolt and empties the list.
/// </summary>
void __cdecl EBolt::Delete_All(void) // RA2: 0x004B23B0
{
	for (int i = 0; i < Bolts.Count(); i++) { // RA2: as above
		delete Bolts[i]; // RA2: as above
	} // RA2: as above
	Bolts.Clear(); // RA2: as above
}
