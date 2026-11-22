// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0079C8D0 (713 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x344d10 (VA 0x00744D10, 720 bytes incl. padding)
// RA2 symbol : ?Add_Buddy@@YIXABVWstring@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9839)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Add_Buddy(Wstring const & name) // RA2: 1.001 0x00744D10, asks the chat service to add the buddy, then adds it to the lists
{
	if (!Is_Valid_New_Buddy(name)) {
		return;
	}
	User user;
	memset(&user, 0, sizeof(user));
	strncpy((char *)user.name, name.text(), 9);
	g_pChat->Unknown_Virtual_E0(&user); // RA2: the buddy add request (YR: RequestBuddyAdd)
	Add_Buddy_Name(name);
	Request_Buddy_Ladders();
}
