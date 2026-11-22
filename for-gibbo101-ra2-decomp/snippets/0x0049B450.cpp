// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0049B450 (54 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x8dc60 (VA 0x0048DC60, 64 bytes incl. padding)
// RA2 symbol : ?Hex_Value@@YIHD@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8214)
// source TU  : src/ra2/coopcamp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x48dc60
int Hex_Value(char digit)
{
    if (digit <= '9' && digit >= '0') {
        return digit - '0';
    }
    if (digit <= 'f' && digit >= 'a') {
        return digit - 'a' + 10;
    }
    if (digit <= 'F' && digit >= 'A') {
        return digit - 'A' + 10;
    }
    return 0;
}
