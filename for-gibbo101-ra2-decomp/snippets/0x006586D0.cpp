// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006586D0 (150 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x22bfa0 (VA 0x0062BFA0, 160 bytes incl. padding)
// RA2 symbol : ?Diplomacy_Dialog@@YIXPAVMouseClass@@@Z
// similarity : 0.9756 (very-similar, masked instruction tokens; shape 0.8913)
// source TU  : src/m85/src/radar.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Shows the diplomacy dialog and waits until it is closed.
/// </summary>
void __fastcall Diplomacy_Dialog(MouseClass * map) // RA2: at 0x00634A00; conquer.cpp calls it with the map, which it does not use
{
	int result; // RA2: the dialog's result is stored in the window's user data
	HWND dialog = OwnerDraw::Begin_Dialog(115, Diplomacy_Dialog_Proc, 0); // RA2: as above
	IgnoreInput = true; // RA2: input to the game is held off while the dialog is up
	Keyboard->Clear(); // RA2: as above
	if (dialog) { // RA2: as above
		SetWindowLong(dialog, DWL_USER, (LONG)&result); // RA2: as above
		OwnerDraw::Display_Dialog(dialog); // RA2: as above
		result = 0; // RA2: as above
		while (true) { // RA2: as above
			if (OwnerDraw::Dialog_Message_Handler()) { // RA2: as above
				result = 1059; // RA2: the dialog ends with the return button's ID when the message loop quits
				break; // RA2: as above
			}
			if (result) { // RA2: as above
				break; // RA2: as above
			}
		}
		OwnerDraw::End_Dialog(dialog); // RA2: as above
	}
	Keyboard->Clear(); // RA2: as above
	IgnoreInput = Scen->IsInputLocked; // RA2: the input flag returns to the scenario's lock state
	Map.Flag_To_Redraw(GS_REDRAW_ALL); // RA2: the whole screen is redrawn
}
