// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0077D970 (23 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x330e70 (VA 0x00730E70, 32 bytes incl. padding)
// RA2 symbol : ?Is_Current_Channel_Flag_8@@YI_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6400)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool Is_Current_Channel_Flag_8(void) // RA2: 0x0073C3A0, channel flag 8 of the current channel
{
	return(Is_Channel_Flag_8(&g_CurrentChannel)); // RA2: as above
}
