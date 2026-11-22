// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0065C630 (11 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x22fc90 (VA 0x0062FC90, 16 bytes incl. padding)
// RA2 symbol : ??0RandomClass@@QAE@I@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6154)
// source TU  : src/m85/src/random.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/***********************************************************************************************
 * RandomClass::RandomClass -- Constructor for the random number class.                        *
 *                                                                                             *
 *    This constructor can take an integer as a parameter. This allows the class to be         *
 *    constructed by assigning an integer to an existing object. The compiler creates a        *
 *    temporary with the constructor and then performs a copy constructor operation.           *
 *                                                                                             *
 * INPUT:   seed  -- The optional starting seed value to use.                                  *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   02/27/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
RandomClass::RandomClass(unsigned seed) :
	Seed(seed)
{
}
