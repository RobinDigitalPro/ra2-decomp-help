// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00732190 (56 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2eba70 (VA 0x006EBA70, 64 bytes incl. padding)
// RA2 symbol : ?All_Of@@YI_NAAV?$DynamicVectorClass@PAVTechnoClass@@@@P6I_NPAVTechnoClass@@PBX@Z2@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8857)
// source TU  : src/ra2/UICmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x2eba70
bool All_Of(DynamicVectorClass<TechnoClass *> & list, TechnoFilterFunc filter, void const * data)
{
    int count = list.Count();
    for (int index = 0; index < count; index++) {
        if (!filter(list[index], data)) {
            return false;
        }
    }
    return true;
}
