// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006357D0 (81 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20a150 (VA 0x0060A150, 96 bytes incl. padding)
// RA2 symbol : ?Planning_Inflate@@YIXAAV?$TRect@H@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8000)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Inflate(Rect & rect, int amount) // RA2: 0x00612570; grows a rectangle by amount on every side; one that would vanish becomes empty
{
	int twice = amount * 2; // RA2: as above
	if (twice < 0 && (twice >= rect.Width || twice >= rect.Height)) { // RA2: as above
		rect.X = 0; // RA2: as above
		rect.Y = 0; // RA2: as above
		rect.Width = 0; // RA2: as above
		rect.Height = 0; // RA2: as above
		return; // RA2: as above
	}
	rect.X -= amount; // RA2: as above
	rect.Y -= amount; // RA2: as above
	rect.Width += twice; // RA2: as above
	rect.Height += twice; // RA2: as above
}
