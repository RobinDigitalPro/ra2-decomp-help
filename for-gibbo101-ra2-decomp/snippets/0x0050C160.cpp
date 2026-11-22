// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0050C160 (10 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xf5030 (VA 0x004F5030, 16 bytes incl. padding)
// RA2 symbol : ?Income_Multiplier@HouseClass@@QBEMXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5000)
// source TU  : src/m85/src/house.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

float HouseClass::Income_Multiplier(void) const // RA2: RA2's form
{
	return(Class->IncomeMult); // RA2: as above
}
