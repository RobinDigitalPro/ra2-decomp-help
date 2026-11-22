// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E3700 (26 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1be780 (VA 0x005BE780, 32 bytes incl. padding)
// RA2 symbol : ?Handle_Reset_Ready@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6667)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Handles the host taking the start reminder back in the guest's lobby.
/// The reminded mark is cleared and the ready button is reset, through the chat service or the network layer.
/// </summary>
void __fastcall Handle_Reset_Ready(void) // RA2: 0x005C3C40, TibSun has no such routine
{
	Session.IsStartReminded = false; // RA2: as above
	if (g_pChat != NULL) {
		Wol_Reset_Ready(); // RA2: as above
	} else {
		Join_Lobby_Reset_Ready(); // RA2: as above
	}
}
