// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00730A90 (58 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2ea8d0 (VA 0x006EA8D0, 64 bytes incl. padding)
// RA2 symbol : ?Show_Command_Message@@YIXPBGH@Z
// similarity : 0.9500 (very-similar, masked instruction tokens; shape 0.8696)
// source TU  : src/ra2/UICmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x2ea8d0
void Show_Command_Message(wchar_t const * text, int timeout = -1)
{
    if (timeout == -1) {
        timeout = 0xF0;
    }
    int color = 3;
    if (PlayerPtr) {
        color = PlayerPtr->ColorScheme;
    }
    SessionMessages.Add_Message(NULL, 0, text, color, 0x4046, timeout, true);
}
