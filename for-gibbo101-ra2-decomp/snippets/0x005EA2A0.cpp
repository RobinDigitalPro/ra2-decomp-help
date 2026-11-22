// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005EA2A0 (313 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c3740 (VA 0x005C3740, 320 bytes incl. padding)
// RA2 symbol : ?Update_Slot_Icons@@YIXPAUHWND__@@@Z
// similarity : 0.9806 (very-similar, masked instruction tokens; shape 0.9231)
// source TU  : src/ra2/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x5c3740
void Update_Slot_Icons(HWND dialog)
{
    for (int i = 0; i < 8; i++) {
        HWND window = GetDlgItem(dialog, Slot_Name_Control_ID(i));
        void * image = NULL;
        MPPlayerNode * node = Session.Slots[i];
        if (Is_Real_Player(node) && !wcscmp(node->Name, Session.GameName)) {
            image = ImageCache.Find(HostIconName, 0);
        } else if (Is_Slot_Ready(i)) {
            image = ImageCache.Find(AcceptIconName, 0);
        }
        Set_Control_Image(window, image);
    }
}
