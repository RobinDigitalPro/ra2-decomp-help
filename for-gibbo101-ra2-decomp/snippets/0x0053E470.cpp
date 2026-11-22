// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0053E470 (74 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x122110 (VA 0x00522110, 80 bytes incl. padding)
// RA2 symbol : ?Audio_File_Find@@YIHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9032)
// source TU  : src/m85/src/audfile.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Returns the index of a window in the table, or -1; the last answer is remembered.
/// </summary>
int __fastcall Audio_File_Find(int id) // RA2: 0x00522BD0
{
	if (AudioFileReady) { // RA2: as above
		HWND * slot = AudioFileWindows; // RA2: as above
		if (id == AudioFileFoundId) { // RA2: as above
			return AudioFileFoundIndex; // RA2: as above
		}
		int index = 0; // RA2: as above
		while (index < AudioFileWindowSlots) { // RA2: as above
			if ((int)*slot == id) { // RA2: as above
				AudioFileFoundId = id; // RA2: as above
				AudioFileFoundIndex = index; // RA2: as above
				return index; // RA2: as above
			}
			index++; // RA2: as above
			slot++; // RA2: as above
		}
	}
	return -1; // RA2: as above
}
