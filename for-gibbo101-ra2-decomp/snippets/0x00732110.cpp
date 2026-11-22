// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00732110 (41 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2eb9f0 (VA 0x006EB9F0, 48 bytes incl. padding)
// RA2 symbol : ?For_Each@@YIXAAV?$DynamicVectorClass@PAVTechnoClass@@@@P6IXPAVTechnoClass@@PBX@Z2@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8627)
// source TU  : src/ra2/UICmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x2eb9f0
void For_Each(DynamicVectorClass<TechnoClass *> & list, TechnoActionFunc action, void const * data)
{
    int count = list.Count();
    for (int index = 0; index < count; index++) {
        action(list[index], data);
    }
}
