// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006CFD20 (8 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x295c30 (VA 0x00695C30, 16 bytes incl. padding)
// RA2 symbol : ?Set_Command_Position@TabClass@@SIXHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.3333)
// source TU  : src/m85/src/tab.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void TabClass::Set_Command_Position(int command, int position)	// RA2: maps the command to a button position
{
	SlotButton[command] = position;	// RA2: as above
}
