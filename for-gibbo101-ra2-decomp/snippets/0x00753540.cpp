// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00753540 (33 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x30b4d0 (VA 0x0070B4D0, 48 bytes incl. padding)
// RA2 symbol : ?Aux_Stream_Unblock@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5455)
// source TU  : src/m85/src/vox.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Aux_Stream_Unblock(void) // RA2: 0x00716910; counts the taunt hold down, not below 0
{
	if (AuxStream != 0) { // RA2: as above
		if (--AuxStreamHold < 0) { // RA2: as above
			AuxStreamHold = 0; // RA2: as above
		}
	}
}
