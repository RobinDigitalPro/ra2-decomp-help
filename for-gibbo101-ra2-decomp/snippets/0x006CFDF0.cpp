// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006CFDF0 (25 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x295d00 (VA 0x00695D00, 32 bytes incl. padding)
// RA2 symbol : ?Is_Team_Command@TabClass@@SIHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6957)
// source TU  : src/m85/src/tab.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int TabClass::Is_Team_Command(int command)	// RA2: whether the command lies in Team01 to Team03
{
	if (command >= Team01Command && command <= Team03Command) {	// RA2: as above
		return(1);	// RA2: as above
	}
	return(0);	// RA2: as above
}
