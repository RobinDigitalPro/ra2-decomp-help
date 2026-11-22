// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0053A120 (15 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x11f1b0 (VA 0x0051F1B0, 16 bytes incl. padding)
// RA2 symbol : ?Is_Flash_Fading@LightningStormClass@@SI_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9091)
// source TU  : src/ra2/Ion.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x11f1b0
bool LightningStormClass::Is_Flash_Fading()
{
    return FlashStatus == 2;
}
