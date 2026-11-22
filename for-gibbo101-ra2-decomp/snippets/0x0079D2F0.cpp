// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0079D2F0 (491 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x345730 (VA 0x00745730, 496 bytes incl. padding)
// RA2 symbol : ?Request_All_Buddy_Ladders@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9840)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Request_All_Buddy_Ladders(void) // RA2: 1.001 0x00745730, puts every buddy into the ladder request list and asks for the first ten
{
	g_BuddyLadderRequests.clear();
	for (int i = 0; i < g_BuddyList.length(); i++) {
		Wstring node;
		g_BuddyList.get(node, i);
		g_BuddyLadderRequests.addTail(node);
	}
	Request_Buddy_Ladders();
}
