// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E2F60 (32 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1bdff0 (VA 0x005BDFF0, 32 bytes incl. padding)
// RA2 symbol : ?Set_Skirmish_Dialog_Text@@YIXPAUHWND__@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Shows the description of the chosen scenario in a lobby dialog.
/// </summary>
/// <param name="dialog">The lobby dialog.</param>
void __fastcall Set_Skirmish_Dialog_Text(HWND dialog) // RA2: 0x005C34B0, TibSun has no such routine
{
	HWND item = GetDlgItem(dialog, 0x5a8); // RA2: as above
	SendMessage(item, OD_SETTEXTW, 0, (LPARAM)Session.Options.ScenarioDescription); // RA2: as above
}
