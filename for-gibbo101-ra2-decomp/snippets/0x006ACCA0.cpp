// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006ACCA0 (187 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x278060 (VA 0x00678060, 192 bytes incl. padding)
// RA2 symbol : ?Any_AI_From@@YI_NH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9673)
// source TU  : src/ra2/Skirmish.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// True when one of the AI slots from slot on has a computer player.
bool Any_AI_From(int slot)
{
    HWND dialog = SkirmishDialog;
    for (int i = slot; i < MAX_SLOTS; i++) {
        int id = AI_Combo_ID(i - 1);
        if (Is_AI_Selected(dialog, id)) {
            return true;
        }
    }
    return false;
}
