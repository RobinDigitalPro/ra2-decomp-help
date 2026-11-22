// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0077D990 (22 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x330e90 (VA 0x00730E90, 32 bytes incl. padding)
// RA2 symbol : ?Is_Channel_Flag_8@@YI_NPBUChannel@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6154)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool Is_Channel_Flag_8(Channel const * channel) // RA2: 0x0073C3C0, only in an Internet game: bit 8 of the channel's reserved word
{
	if (Session.Type != GAME_INTERNET) return(false); // RA2: as above
	return((channel->reserved >> 8) & 1); // RA2: as above
}
