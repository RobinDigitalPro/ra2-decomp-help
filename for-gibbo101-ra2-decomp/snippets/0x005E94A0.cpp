// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E94A0 (44 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c2e40 (VA 0x005C2E40, 48 bytes incl. padding)
// RA2 symbol : ?Get_AI_Difficulty@@YIHPAUNodeNameType@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8750)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int __fastcall Get_AI_Difficulty(NodeNameType * entry) // RA2: 0x005C93D0, not in TibSun; 2 for the easy, 1 for the medium and 0 for the hard computer player, -1 for any other entry
{
	int difficulty = -1; // RA2: as above
	if (entry == LobbyEntries[2]) { // RA2: as above
		return(2); // RA2: as above
	}
	if (entry == LobbyEntries[3]) { // RA2: as above
		return(1); // RA2: as above
	}
	if (entry == LobbyEntries[4]) { // RA2: as above
		difficulty = 0; // RA2: as above
	}
	return(difficulty); // RA2: as above
}
