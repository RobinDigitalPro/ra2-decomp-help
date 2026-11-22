// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0053A0E0 (27 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x11f170 (VA 0x0051F170, 32 bytes incl. padding)
// RA2 symbol : ?Active_Or_Deferred@LightningStormClass@@SIHXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8000)
// source TU  : src/ra2/Ion.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x11f170
int LightningStormClass::Active_Or_Deferred()
{
    if (IsActive || Deferment > 0) {
        return true;
    }
    return false;
}
