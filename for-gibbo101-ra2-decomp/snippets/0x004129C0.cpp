// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004129C0 (119 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x12720 (VA 0x00412720, 128 bytes incl. padding)
// RA2 symbol : ?Append_Bin@AircraftTrackerClass@@QAEXH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9204)
// source TU  : src/m85/src/atracker.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Adds the objects of one bin to the working list.
/// </summary>
void AircraftTrackerClass::Append_Bin(int index) // RA2: 0x00412720
{
	DynamicVectorClass<TechnoClass *> & bin = TrackerVectors[index]; // RA2: the bin to copy
	int count = bin.Count();
	for (int i = 0; i < count; i++) {
		CurrentVector.Add(bin.GetItem(i)); // RA2: the element is fetched through the vector's virtual at +0x18 (YR name GetItem)
	}
}
