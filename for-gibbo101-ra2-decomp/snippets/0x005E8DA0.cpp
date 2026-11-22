// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E8DA0 (21 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c2b00 (VA 0x005C2B00, 32 bytes incl. padding)
// RA2 symbol : ?Seat_First_Player@@YIXH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.4762)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Seat_First_Player(int slot) // RA2: 0x005C8CD0, not in TibSun; the first player of the list takes the slot and the local slot is told
{
	Session.LocalSlot = slot; // RA2: as above
	Session.Slots[slot] = Session.Players[0]; // RA2: as above
}
