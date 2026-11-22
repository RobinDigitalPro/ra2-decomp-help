// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E8D90 (8 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c2af0 (VA 0x005C2AF0, 16 bytes incl. padding)
// RA2 symbol : ?Set_Slot@@YIXHPAVMPPlayerNode@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.3333)
// source TU  : src/ra2/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x5c2af0
void Set_Slot(int slot, MPPlayerNode * node)
{
    Session.Slots[slot] = node;
}
