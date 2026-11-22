// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E9850 (156 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c3020 (VA 0x005C3020, 160 bytes incl. padding)
// RA2 symbol : ?Clear_Accept_States@@YIXXZ
// similarity : 0.9796 (very-similar, masked instruction tokens; shape 0.9608)
// source TU  : src/ra2/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x5c3020
void Clear_Accept_States()
{
    if (Current_Dialog_ID() != 0xBC) {
        EnableWindow(GetDlgItem(Find_Network_Dialog(), 0x59F), TRUE);
    }
    int count = Session.Players.ActiveCount;
    for (int i = 0; i < count; i++) {
        if (wcscmp(Session.Players[i]->Name, Session.GameName) != 0) {
            MPPlayerNode * node = Session.Players[i];
            if (node->AcceptState) {
                node->AcceptState = 0;
            }
        }
    }
}
