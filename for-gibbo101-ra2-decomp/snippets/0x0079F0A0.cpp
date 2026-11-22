// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0079F0A0 (152 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x347440 (VA 0x00747440, 160 bytes incl. padding)
// RA2 symbol : ?Find_Channel@@YI_NABVWstring@@AAV?$ArrayList@UChannel@@@@AAUChannel@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9394)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Find_Channel(Wstring const & name, ArrayList<Channel> & list, Channel & result) // RA2: 1.001 0x00747440, the channel of the list with this name
{
	memset(&result, 0, sizeof(Channel));
	for (int i = 0; i < list.length(); i++) {
		list.get(result, i);
		if (stricmp((char *)result.name, name.text()) == 0) {
			return(true);
		}
	}
	memset(&result, 0, sizeof(Channel));
	return(false);
}
