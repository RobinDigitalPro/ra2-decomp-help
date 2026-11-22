// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007A2970 (100 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x34a380 (VA 0x0074A380, 112 bytes incl. padding)
// RA2 symbol : ?Open_Buddy_Dialog@@YIXXZ
// similarity : 0.9600 (very-similar, masked instruction tokens; shape 0.8065)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Open_Buddy_Dialog(void) // RA2: 1.001 0x0074A380, after a quick match: offers the opponent as a buddy (dialog 0x122)
{
	g_PlayingNetGame = false;
	if (!g_ConnectionLost && Get_Add_Match_Buddies() && Is_Valid_New_Buddy(g_MatchOpponentName)) {
		SimpleWonlineDialogControl control;
		OwnerDraw::Controlled_Dialog(0x122, WOL_Add_Opponent_Dialog_Proc, &control);
	}
}
