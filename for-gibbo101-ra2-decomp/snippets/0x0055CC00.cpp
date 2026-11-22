// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0055CC00 (8 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x13d630 (VA 0x0053D630, 16 bytes incl. padding)
// RA2 symbol : ?Enter_Main_Loop@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.3333)
// source TU  : src/m85/src/mainloop.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: marks Main_Loop as running.
/// </summary>
void Enter_Main_Loop(void) // RA2 has this routine (0x0053F470): it sets the flag Main_Loop sets
{ // RA2: as above
	InMainLoop = true; // RA2: as above
}
