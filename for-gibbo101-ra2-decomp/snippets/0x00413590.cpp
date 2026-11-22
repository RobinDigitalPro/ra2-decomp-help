// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00413590 (6 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x132d0 (VA 0x004132D0, 16 bytes incl. padding)
// RA2 symbol : ?Tracker_Return_750@@YIIXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.2857)
// source TU  : src/m85/src/atracker.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Gives the number 750; nothing calls it, and the executable shows no use of the number here.
/// </summary>
unsigned int Tracker_Return_750(void) // RA2: 0x004132D0
{
	return 750;
}
