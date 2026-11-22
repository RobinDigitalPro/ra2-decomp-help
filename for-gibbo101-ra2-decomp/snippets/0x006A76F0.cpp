// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006A76F0 (103 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2733c0 (VA 0x006733C0, 112 bytes incl. padding)
// RA2 symbol : ?Start_Tab_Flash@SidebarClass@@QAEXH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8831)
// source TU  : src/m85/src/sidebar.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void SidebarClass::Start_Tab_Flash(int index) // RA2: as above
{
	int delay = 10 - Frame % 10; // RA2: as above
	TabButton[index].Start_Flashing(10, delay, (Frame + delay) / 10 % 2 == 0); // RA2: as above
	Map.IsForceCompleteRedraw = true; // RA2: as above
	Map.Flag_To_Redraw();
}
