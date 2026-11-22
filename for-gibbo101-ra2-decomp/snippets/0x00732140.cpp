// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00732140 (67 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2eba20 (VA 0x006EBA20, 80 bytes incl. padding)
// RA2 symbol : ?For_Each_If@@YIXAAV?$DynamicVectorClass@PAVTechnoClass@@@@P6I_NPAVTechnoClass@@PBX@ZP6IX12@Z22@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8312)
// source TU  : src/ra2/UICmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x2eba20
void For_Each_If(DynamicVectorClass<TechnoClass *> & list, TechnoFilterFunc filter, TechnoActionFunc action, void const * filter_data, void const * action_data)
{
    int count = list.Count();
    for (int index = 0; index < count; index++) {
        TechnoClass * techno = list[index];
        if (filter(techno, filter_data)) {
            action(techno, action_data);
        }
    }
}
