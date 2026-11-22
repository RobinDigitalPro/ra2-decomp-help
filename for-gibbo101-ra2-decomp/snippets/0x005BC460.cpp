// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005BC460 (104 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x19a850 (VA 0x0059A850, 112 bytes incl. padding)
// RA2 symbol : ?Debug_Window_Select_Page@@YIXH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9000)
// source TU  : src/m85/src/motlib.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Debug_Window_Select_Page(int index) // level-2 1.001: 0x19A850, adopted from gibbo101 (FUN_005BC460)
{
	DebugPage * page = DebugPages[index];
	CurrentDebugPage = page;
	page->Clear(); // level-2 1.001: inline
	CurrentDebugPage->Refresh(0, 0, 80, 25);
}
