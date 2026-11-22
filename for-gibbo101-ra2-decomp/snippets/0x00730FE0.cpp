// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00730FE0 (116 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2eacf0 (VA 0x006EACF0, 128 bytes incl. padding)
// RA2 symbol : ?Scatter_Command@@YIXXZ
// similarity : 0.9565 (very-similar, masked instruction tokens; shape 0.8846)
// source TU  : src/ra2/UICmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x2eacf0 (ScatterObject)
void Scatter_Command()
{
    if (CurrentObjects.Count() > 0) {
        bool ok = true;
        int count = CurrentObjects.Count();
        for (int index = 0; index < count; index++) {
            TechnoClass * techno = (TechnoClass *)CurrentObjects[index];
            if (techno && techno->Flag1 && techno->Slot_039_Query()) {
                ok = techno->Can_Do_Command(7);
                if (!ok) {
                    break;
                }
            }
        }
        if (ok) {
            Play_Sound(Rule->ScatterSound, 1.0f, 0x2000, 0);
        }
    }
}
