// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00413490 (3 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x131d0 (VA 0x004131D0, 16 bytes incl. padding)
// RA2 symbol : ?Detach@AircraftTrackerClass@@QAEXPAVAbstractClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.1333)
// source TU  : src/m85/src/atracker.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Does nothing: the tracker needs no work when an object it may hold goes away.
/// </summary>
void AircraftTrackerClass::Detach(AbstractClass * target) // RA2: 0x004131D0
{
}
