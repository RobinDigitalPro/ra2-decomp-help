// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00731EB0 (187 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2eb790 (VA 0x006EB790, 192 bytes incl. padding)
// RA2 symbol : ?Collect_Technos@@YIPAV?$DynamicVectorClass@PAVTechnoClass@@@@P6I_NPAVTechnoClass@@PBX@Z1@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9682)
// source TU  : src/ra2/UICmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x2eb790
DynamicVectorClass<TechnoClass *> * Collect_Technos(TechnoFilterFunc filter, void const * data)
{
    DynamicVectorClass<TechnoClass *> * list = new DynamicVectorClass<TechnoClass *>;
    int count = Technos.Count();
    for (int index = 0; index < count; index++) {
        TechnoClass * techno = Technos[index];
        if (filter(techno, data)) {
            list->Add(techno);
        }
    }
    return list;
}
