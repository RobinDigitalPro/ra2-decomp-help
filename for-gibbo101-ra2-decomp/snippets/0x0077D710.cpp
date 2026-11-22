// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0077D710 (5 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x330bf0 (VA 0x00730BF0, 16 bytes incl. padding)
// RA2 symbol : ?Wait_Callback_Thunk@@YI_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.1538)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool Wait_Callback_Thunk(void) // RA2: 0x0073C120, a jump to WOL_Wait_Callback (the message box callback)
{
	return(WOL_Wait_Callback()); // RA2: as above
}
