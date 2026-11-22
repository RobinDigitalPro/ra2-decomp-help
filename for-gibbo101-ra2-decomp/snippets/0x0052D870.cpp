// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0052D870 (297 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x112cd0 (VA 0x00512CD0, 304 bytes incl. padding)
// RA2 symbol : ?Movie_List_Dialog_Proc@@YGHPAUHWND__@@IIJ@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9686)
// source TU  : src/m85/src/init.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/***********************************************************************************************
 * Movie_List_Dialog_Proc -- Message handler of the list of movies.                            *
 *                                                                                             *
 *    The dialog lists the movies the player has unlocked; the choice is the list entry the    *
 *    player picked, or -1.                                                                    *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   RA2 has this dialog; it is not in TibSun.                                                 *
 *=============================================================================================*/
BOOL CALLBACK Movie_List_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) // RA2: 0x005134C0, not in TibSun
{
	bool chosen = false; // RA2: as above
	HWND list = GetDlgItem(window, 0x744); // RA2: as above

	int rc = OwnerDraw::Default_Dialog_Proc(window, message, wparam, lparam); // RA2: as above
	if (rc) { // RA2: as above
		return(rc); // RA2: as above
	} // RA2: as above

	int * choice = (int *)GetWindowLong(window, DWL_USER); // RA2: as above

	switch (message) { // RA2: as above
		case WM_USER + 151: // RA2: as above
			if (list != NULL) { // RA2: as above
				Options.Fill_Movie_List(list); // RA2: as above
				if (SendMessage(list, LB_SETCURSEL, MovieListChoice, 0) == LB_ERR) { // RA2: as above
					SendMessage(list, LB_SETCURSEL, 0, 0); // RA2: as above
				} // RA2: as above
			} else { // RA2: as above
				if (choice != NULL) { // RA2: as above
					*choice = -1; // RA2: as above
				} // RA2: as above
				return(FALSE); // RA2: as above
			} // RA2: as above
			break; // RA2: as above

		case WM_COMMAND: // RA2: as above
			switch (LOWORD(wparam)) { // RA2: as above
				case 0x686: // RA2: as above
					if (choice != NULL) { // RA2: as above
						*choice = -1; // RA2: as above
					} // RA2: as above
					break; // RA2: as above

				case 0x744: // RA2: as above
					if (HIWORD(wparam) == 0) { // RA2: as above
						chosen = true; // RA2: as above
					} // RA2: as above
					break; // RA2: as above

				case 0x745: // RA2: as above
					chosen = true; // RA2: as above
					break; // RA2: as above
			}
			break; // RA2: as above
	}

	if (list != NULL && chosen) { // RA2: as above
		int index = SendMessage(list, LB_GETCURSEL, 0, 0); // RA2: as above
		MovieListChoice = index; // RA2: as above
		if (index != LB_ERR) { // RA2: as above
			int movie = SendMessage(list, LB_GETITEMDATA, index, 0); // RA2: as above
			if (movie != 0 && choice != NULL) { // RA2: as above
				*choice = movie; // RA2: as above
			} // RA2: as above
		} // RA2: as above
	} // RA2: as above

	return(FALSE); // RA2: as above
}
