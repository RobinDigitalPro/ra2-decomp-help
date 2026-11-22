// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E8AE0 (93 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c2860 (VA 0x005C2860, 96 bytes incl. padding)
// RA2 symbol : ?Fill_Slots@@YIXXZ
// similarity : 0.9655 (very-similar, masked instruction tokens; shape 0.9508)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Fill_Slots(void) // RA2: 0x005C8A10, not in TibSun; the slots up to the limit are open, the others closed
{
	int limit = Get_Lobby_Slot_Limit(); // RA2: as above
	for (int i = 0; i < limit; i++) { // RA2: as above
		Session.Slots[i] = LobbyEntries[0]; // RA2: as above
	}
	for (int j = limit; j < 8; j++) { // RA2: as above
		Session.Slots[j] = LobbyEntries[1]; // RA2: as above
	}
}
