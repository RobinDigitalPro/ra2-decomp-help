// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00733CD0 (307 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2ed2c0 (VA 0x006ED2C0, 320 bytes incl. padding)
// RA2 symbol : ?Collect_Type_Names@@YIPAV?$DynamicVectorClass@PBD@@PAV?$DynamicVectorClass@PAVTechnoClass@@@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9486)
// source TU  : src/ra2/UICmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x2ed2c0
DynamicVectorClass<char const *> * Collect_Type_Names(DynamicVectorClass<TechnoClass *> * list)
{
    DynamicVectorClass<char const *> * names = new DynamicVectorClass<char const *>;
    int count = list->Count();
    for (int index = 0; index < count; index++) {
        char const * name = (*list)[index]->Class_Of()->ID;
        if (Find_Name(*names, name) == -1) {
            names->Add(name);
        }
    }
    return names;
}
