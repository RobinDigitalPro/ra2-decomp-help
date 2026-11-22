// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007A2730 (21 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x34a150 (VA 0x0074A150, 32 bytes incl. padding)
// RA2 symbol : ?Wol_Send_Start_Reminder@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5926)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// level-2 1.001 (wol_b): the tail of wonline.cpp after Reset_Wait_Events (0x741080-0x74A1F0); proposed source, verified in a scratch copy
void Wol_Send_Start_Reminder(void) // RA2: 0x0075C960 (1.001 0x0074A150), sends the game option "G" through the chat service
{
	if (g_pChat) {
		g_pChat->RequestPublicGameOptions("G");
	}
}
