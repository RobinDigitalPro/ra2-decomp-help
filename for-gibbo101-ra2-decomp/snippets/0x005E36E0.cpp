// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E36E0 (26 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1be760 (VA 0x005BE760, 32 bytes incl. padding)
// RA2 symbol : ?Handle_Start_Reminder@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6667)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Handles the host's start reminder in the guest's lobby.
/// The guest is marked as reminded and told, through the chat service or the network layer.
/// </summary>
void __fastcall Handle_Start_Reminder(void) // RA2: 0x005C3C20, TibSun has no such routine
{
	Session.IsStartReminded = true; // RA2: as above
	if (g_pChat != NULL) {
		Wol_Handle_Start_Reminder(); // RA2: as above
	} else {
		Join_Lobby_Start_Reminder(); // RA2: as above
	}
}
