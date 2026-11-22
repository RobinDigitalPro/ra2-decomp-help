// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00731AA0 (68 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2eb380 (VA 0x006EB380, 80 bytes incl. padding)
// RA2 symbol : ?All_Can_Attack_Move@@YI_NXZ
// similarity : 0.9688 (very-similar, masked instruction tokens; shape 0.8421)
// source TU  : src/ra2/UICmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x2eb380
bool All_Can_Attack_Move()
{
    int count = CurrentObjects.Count();
    for (int index = 0; index < count; index++) {
        ObjectClass * object = CurrentObjects[index];
        if (Is_Techno(object) && !((TechnoClass *)object)->Slot_275_Query()) {
            return false;
        }
    }
    return true;
}
