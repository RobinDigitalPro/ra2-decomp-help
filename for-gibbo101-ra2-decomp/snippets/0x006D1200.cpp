// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006D1200 (752 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2970f0 (VA 0x006970F0, 752 bytes incl. padding)
// RA2 symbol : ?Show_Buttons@TabClass@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/tab.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void TabClass::Show_Buttons(void)	// RA2: adds the open bar's buttons and their tool tips
{
	Add_Command_Buttons();	// RA2: as above
	Add_A_Button(ThumbOpenButton);	// RA2: as above
	Add_Button_ToolTip(Get_Button(AttackMoveCommand), "Tip:AttackMove");	// RA2: as above
	Add_Button_ToolTip(Get_Button(BeaconCommand), "Tip:Beacon");	// RA2: as above
	Add_Button_ToolTip(Get_Button(CheerCommand), "Tip:Cheer");	// RA2: as above
	Add_Button_ToolTip(Get_Button(DeployCommand), "Tip:Deploy");	// RA2: as above
	Add_Button_ToolTip(Get_Button(GuardCommand), "Tip:Guard");	// RA2: as above
	Add_Button_ToolTip(Get_Button(PlanningModeCommand), "Tip:PlanningMode");	// RA2: as above
	{
		ShapeButtonClass * button = Get_Button(StopCommand);	// RA2: as above
		Add_Button_ToolTip(button, "Tip:Stop");	// RA2: as above
	}
	{
		ShapeButtonClass * button = Get_Button(Team01Command);	// RA2: as above
		Add_Button_ToolTip(button, "Tip:Team01");	// RA2: as above
	}
	{
		ShapeButtonClass * button = Get_Button(Team02Command);	// RA2: as above
		Add_Button_ToolTip(button, "Tip:Team02");	// RA2: as above
	}
	{
		ShapeButtonClass * button = Get_Button(Team03Command);	// RA2: as above
		Add_Button_ToolTip(button, "Tip:Team03");	// RA2: as above
	}
	{
		ShapeButtonClass * button = Get_Button(TypeSelectCommand);	// RA2: as above
		Add_Button_ToolTip(button, "Tip:TypeSelect");	// RA2: as above
	}
	Add_Button_ToolTip(&ThumbOpenButton, "Tip:ThumbOpen");	// RA2: as above
}
