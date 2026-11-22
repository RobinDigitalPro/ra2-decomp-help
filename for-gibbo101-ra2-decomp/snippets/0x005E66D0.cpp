// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E66D0 (27 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c0830 (VA 0x005C0830, 32 bytes incl. padding)
// RA2 symbol : ?Get_Selected_Scenario_Row@@YIHXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7619)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int Get_Selected_Scenario_Row(void) // RA2: 0x005C67A0, the highlighted row of the map list (the executable also keeps this call inline in Scenario_Select_Callback)
{
	return(SendDlgItemMessage(ScenarioPick, IDC_AILEVEL_SLIDER, LB_GETCURSEL, 0, 0)); // RA2: as above
}
