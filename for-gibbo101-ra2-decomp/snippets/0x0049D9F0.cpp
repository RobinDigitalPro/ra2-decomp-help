// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0049D9F0 (112 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x90280 (VA 0x00490280, 112 bytes incl. padding)
// RA2 symbol : ?Coop_House_From_Name@@YIHPBD@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/ra2/coopcamp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x490280: house type index of a campaign house name, -2 for "<random>", -1 when unknown.
int Coop_House_From_Name(char const * name)
{
    if (_stricmp(name, "<random>") == 0) {
        return -2;
    }
    if (name != NULL) {
        for (int index = 0; index < HouseTypes.Count(); index++) {
            HouseTypeClass * house = HouseTypes[index];
            if (_stricmp(house->Name, name) == 0 || _stricmp(house->ID, name) == 0) {
                return index;
            }
        }
    }
    return -1;
}
