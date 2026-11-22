// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0079C650 (629 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x344a90 (VA 0x00744A90, 640 bytes incl. padding)
// RA2 symbol : ?Add_Buddy_Name@@YIXABVWstring@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9720)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Add_Buddy_Name(Wstring const & name) // RA2: 1.001 0x00744A90, adds a valid new name to the buddy lists and asks for its channel
{
	if (!Is_Valid_New_Buddy(name)) {
		return;
	}
	Wstring entry(name);
	g_BuddyList.addTail(entry);
	g_BuddyRequests.addTail(entry);
	g_BuddyLadderRequests.addTail(entry);
	Request_Next_Buddy_Find();
}
