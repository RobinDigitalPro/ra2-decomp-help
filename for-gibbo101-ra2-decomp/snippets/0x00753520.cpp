// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00753520 (21 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x30b4b0 (VA 0x0070B4B0, 32 bytes incl. padding)
// RA2 symbol : ?Aux_Stream_Hold@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5600)
// source TU  : src/m85/src/vox.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Aux_Stream_Hold(void) // RA2: 0x007168F0; counts the taunt hold up while there is a taunt stream
{
	if (AuxStream != 0) { // RA2: as above
		AuxStreamHold++; // RA2: as above
	}
}
