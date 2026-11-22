// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007A27D0 (34 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x34a1f0 (VA 0x0074A1F0, 48 bytes incl. padding)
// RA2 symbol : ?Wol_Reset_Ready@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5882)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Wol_Reset_Ready(void) // RA2: 0x0075CA00 (1.001 0x0074A1F0), sends message 0x4DC to the ready button
{
	HWND dialog = WS_Top_Window();
	HWND item = GetDlgItem(dialog, 0x59F);
	SendMessage(item, 0x4DC, 0, 0);
}
