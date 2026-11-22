// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0049B540 (206 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x8dd50 (VA 0x0048DD50, 208 bytes incl. padding)
// RA2 symbol : ?Decode_Name@@YIPADPBD@Z
// similarity : 0.9882 (very-similar, masked instruction tokens; shape 0.9884)
// source TU  : src/ra2/coopcamp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x48dd50
char * Decode_Name(char const * string)
{
    char * ptr = DecodeBuffer;
    while (*string != '\0') {
        if (*string == '=') {
            if (string[1] == '\0') break;
            *ptr = (char)Hex_Value(string[1]);
            string++;
            if (string[1] != '\0') {
                *ptr <<= 4;
                *ptr |= (char)Hex_Value(string[1]);
                string++;
            }
        } else {
            *ptr = *string;
        }
        string++;
        ptr++;
    }
    *ptr = '\0';
    return DecodeBuffer;
}
