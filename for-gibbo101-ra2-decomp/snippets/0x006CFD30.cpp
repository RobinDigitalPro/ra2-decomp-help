// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006CFD30 (8 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x295c40 (VA 0x00695C40, 16 bytes incl. padding)
// RA2 symbol : ?Get_Command_Position@TabClass@@SIHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.3333)
// source TU  : src/m85/src/tab.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int TabClass::Get_Command_Position(int command)	// RA2: the button position of a command
{
	return(SlotButton[command]);	// RA2: as above
}
