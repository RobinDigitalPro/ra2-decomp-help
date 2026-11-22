// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E8B60 (131 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c28e0 (VA 0x005C28E0, 144 bytes incl. padding)
// RA2 symbol : ?Reset_Slots@@YIXXZ
// similarity : 0.9706 (very-similar, masked instruction tokens; shape 0.8395)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Reset_Slots(void) // RA2: 0x005C8A90, not in TibSun; the slots are open or closed again, nobody is seated, the computer players are cleared
{
	int limit = Get_Lobby_Slot_Limit(); // RA2: as above
	for (int i = 0; i < limit; i++) { // RA2: as above
		Session.Slots[i] = LobbyEntries[0]; // RA2: as above
	}
	for (int j = limit; j < 8; j++) { // RA2: as above
		Session.Slots[j] = LobbyEntries[1]; // RA2: as above
	}
	Session.LocalSlot = -1; // RA2: as above
	Session.Options.Reset_AI(); // RA2: as above
	SlotNamesOld[0] = L'\0'; // RA2: as above
	SlotNames[0] = L'\0'; // RA2: as above
}
