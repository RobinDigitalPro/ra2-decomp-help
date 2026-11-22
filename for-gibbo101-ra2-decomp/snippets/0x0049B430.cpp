// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0049B430 (25 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x8dc40 (VA 0x0048DC40, 32 bytes incl. padding)
// RA2 symbol : ?Hex_Digit@@YIDH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7742)
// source TU  : src/ra2/coopcamp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x48dc40
char Hex_Digit(int value)
{
    if (value >= 0 && value <= 15) {
        if (value < 10) {
            return (char)(value + '0');
        }
        return (char)(value + 'A' - 10);
    }
    return 0;
}
