// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0053E4C0 (33 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x122160 (VA 0x00522160, 48 bytes incl. padding)
// RA2 symbol : ?Audio_File_Window@@YIPAUHWND__@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6154)
// source TU  : src/m85/src/audfile.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Returns the window with the given index in the table, or NULL.
/// </summary>
HWND __fastcall Audio_File_Window(int index) // RA2: 0x00522C20
{
	if (AudioFileReady && index >= 0 && index < AudioFileWindowSlots) { // RA2: as above
		return AudioFileWindows[index]; // RA2: as above
	}
	return NULL; // RA2: as above
}
