// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0053E420 (67 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1220c0 (VA 0x005220C0, 80 bytes incl. padding)
// RA2 symbol : ?Remove_Audio_File_Window@@YIXPAUHWND__@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7937)
// source TU  : src/m85/src/audfile.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Takes a window out of the table again.
/// </summary>
void __fastcall Remove_Audio_File_Window(HWND window) // RA2: 0x00522B80
{
	if (AudioFileReady && window != NULL) { // RA2: as above
		HWND * slot = AudioFileWindows; // RA2: as above
		for (int index = 1; index < AudioFileWindowSlots; index++, slot++) { // RA2: as above
			if (*slot == window) { // RA2: as above
				*slot = NULL; // RA2: as above
				AudioFileWindowCount--; // RA2: as above
				return; // RA2: as above
			}
		}
	}
}
