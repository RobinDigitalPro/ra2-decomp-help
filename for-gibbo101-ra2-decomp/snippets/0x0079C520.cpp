// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0079C520 (297 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x344960 (VA 0x00744960, 304 bytes incl. padding)
// RA2 symbol : ?Is_Valid_New_Buddy@@YI_NABVWstring@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9652)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool Is_Valid_New_Buddy(Wstring const & name) // RA2: 1.001 0x00744960, the name may be added as a buddy: not empty, not the player, no separators and not yet in the list
{
	Wstring lower(name);
	lower.toLower();
	if (name.length() == 0) {
		return(false);
	}
	if (((Wstring const &)lower).toLower() == ((Wstring const &)g_NickName).toLower()) {
		return(false);
	}
	if (name.containsAny(" ,;")) {
		return(false);
	}
	for (int i = 0; i < g_BuddyList.length(); i++) {
		Wstring entry;
		g_BuddyList.get(entry, i);
		entry.toLower();
		if (entry == lower) {
			return(false);
		}
	}
	return(true);
}
