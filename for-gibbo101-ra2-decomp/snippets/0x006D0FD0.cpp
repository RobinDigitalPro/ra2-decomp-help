// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006D0FD0 (345 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x296ec0 (VA 0x00696EC0, 352 bytes incl. padding)
// RA2 symbol : ?Setup_Command_Buttons@TabClass@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9694)
// source TU  : src/m85/src/tab.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void TabClass::Setup_Command_Buttons(void)	// RA2: gives each command button its place, shape and click flags
{
	for (int index = 0; index < BUTTON_COUNT; index++) {	// RA2: as above
		CommandButtons[index].Set_Shape(NULL, 0, 0);	// RA2: as above
	}
	Rect area = *ThumbClosedRect;	// RA2: as above
	int right = area.X + area.Width;	// RA2: as above
	for (int command = 0; command < BUTTON_COUNT; command++) {	// RA2: as above
		ShapeButtonClass * button = Get_Button(command);	// RA2: as above
		if (button) {	// RA2: as above
			Rect box = *ButtonSlotRect;	// RA2: as above
			int x = SlotButton[command] * SlotPitch + box.X;	// RA2: as above
			int y = SlotTop;	// RA2: as above
			if (box.Width + x <= right) {	// RA2: as above
				button->ID = command + BUTTON_COMMAND_FIRST;	// RA2: as above
				button->ShapeDrawer = SidebarDrawer;	// RA2: as above
				button->IsOn = false;	// RA2: as above
				button->IsToggleType = 0;	// RA2: as above
				button->Set_Flags(GadgetClass::LEFTPRESS | GadgetClass::LEFTRELEASE);	// RA2: as above
				button->Set_Position(x, y);	// RA2: as above
				button->Set_Shape(ButtonShapes[command], 0, 0);	// RA2: as above
			}
		}
	}
	ShapeButtonClass * planning = Get_Button(PlanningModeCommand);	// RA2: as above
	if (planning) {	// RA2: as above
		planning->IsToggleType = 1;	// RA2: as above
		planning->ReflectButtonState = true;	// RA2: as above
	}
	for (int team = Team01Command; team <= Team03Command; team++) {	// RA2: as above
		ShapeButtonClass * button = Get_Button(team);	// RA2: as above
		if (button) {	// RA2: as above
			button->Set_Flags(GadgetClass::LEFTPRESS | GadgetClass::LEFTRELEASE | GadgetClass::RIGHTPRESS | GadgetClass::RIGHTRELEASE);	// RA2: as above
		}
	}
}
