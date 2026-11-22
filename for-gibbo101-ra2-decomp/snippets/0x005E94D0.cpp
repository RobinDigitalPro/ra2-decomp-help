// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E94D0 (62 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c2e70 (VA 0x005C2E70, 64 bytes incl. padding)
// RA2 symbol : ?Count_AI_Slots@@YIHXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9615)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int Count_AI_Slots(void) // RA2: 0x005C9400, not in TibSun; the slots holding an easy, medium or hard computer player
{
	NodeNameType * easy = LobbyEntries[2]; // RA2: the entries are read once into locals
	NodeNameType * medium = LobbyEntries[3]; // RA2: as above
	NodeNameType * hard = LobbyEntries[4]; // RA2: as above
	int count = 0; // RA2: as above
	for (int i = 0; i < 8; i++) { // RA2: as above
		NodeNameType * entry = Session.Slots[i]; // RA2: as above
		if (entry != NULL && (entry == easy || entry == medium || entry == hard)) { // RA2: as above
			count++; // RA2: as above
		}
	}
	return(count); // RA2: as above
}
