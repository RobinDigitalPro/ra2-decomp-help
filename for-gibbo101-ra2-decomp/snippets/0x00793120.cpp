// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00793120 (117 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x33f0f0 (VA 0x0073F0F0, 128 bytes incl. padding)
// RA2 symbol : ?User_Is_Channel_Owner@@YI_NABVWstring@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9043)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool User_Is_Channel_Owner(Wstring const & name) // RA2: 0x0074D9E0, not in TibSun: the channel owner (the user with flag 1) has this name; no caller (expanded where it is used)
{
	User * owner = Find_Owner_User(); // RA2: expanded here
	if (owner == NULL) { // RA2: as above
		return(false); // RA2: as above
	}
	if (stricmp((char *)owner->name, name.text()) == 0) { // RA2: as above
		return(true); // level-2 1.001: the if form (no sete) lets OnPublicGameOptions keep its early-return layout
	}
	return(false); // RA2: as above
}
