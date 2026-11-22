// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00730EA0 (129 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2eabb0 (VA 0x006EABB0, 144 bytes incl. padding)
// RA2 symbol : ?Stop_Command@@YIXXZ
// similarity : 0.9608 (very-similar, masked instruction tokens; shape 0.8718)
// source TU  : src/ra2/UICmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x2eabb0 (StopObject)
void Stop_Command()
{
    if (CurrentObjects.Count() > 0) {
        bool ok = true;
        int count = CurrentObjects.Count();
        for (int index = 0; index < count; index++) {
            TechnoClass * techno = (TechnoClass *)CurrentObjects[index];
            if (techno && techno->Flag1 && (techno->Slot_039_Query() || techno->Slot_038_Query())) {
                ok = techno->Can_Do_Command(6);
                if (!ok) {
                    break;
                }
            }
        }
        if (ok) {
            Play_Sound(Rule->StopSound, 1.0f, 0x2000, 0);
        }
    }
}
