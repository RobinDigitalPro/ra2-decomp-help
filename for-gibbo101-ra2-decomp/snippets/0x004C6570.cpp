// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004C6570 (45 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xb5b90 (VA 0x004B5B90, 48 bytes incl. padding)
// RA2 symbol : ?Next_Event_Number@@YIEXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9032)
// source TU  : src/ra2/Event.CPP (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x4b5b90: running event number within the current frame (no caller in GAME.EXE).
unsigned char Next_Event_Number()
{
    if (Frame != EventNumberFrame) {
        EventNumber = 0;
    }
    return EventNumber++;
}
