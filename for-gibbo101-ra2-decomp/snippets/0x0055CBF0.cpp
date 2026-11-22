// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0055CBF0 (6 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x13d620 (VA 0x0053D620, 16 bytes incl. padding)
// RA2 symbol : ?Is_In_Main_Loop@@YI_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.2857)
// source TU  : src/m85/src/mainloop.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: tells whether Main_Loop is running.
/// </summary>
bool Is_In_Main_Loop(void) // RA2 has this routine (0x0053F460): it reads the flag Main_Loop sets
{ // RA2: as above
	return InMainLoop; // RA2: as above
}
