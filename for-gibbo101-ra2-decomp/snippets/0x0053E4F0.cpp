// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0053E4F0 (95 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x122190 (VA 0x00522190, 96 bytes incl. padding)
// RA2 symbol : ?Audio_File_Create_Stream@@YIHPBD@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9831)
// source TU  : src/m85/src/audfile.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Creates the file a recording is written to ("wb") and switches to recording.
/// </summary>
int __fastcall Audio_File_Create_Stream(char const * name) // RA2: 0x00522C50
{
	if (AudioFileReady && AudioFileStream == NULL) { // RA2: as above
		EnterCriticalSection(&AudioFileLock); // RA2: as above
		AudioFileStream = fopen(name, "wb"); // RA2: as above
		if (AudioFileStream != NULL) { // RA2: as above
			AudioFileMode = 1; // RA2: as above
		}
		LeaveCriticalSection(&AudioFileLock); // RA2: as above
		return AudioFileStream != NULL; // RA2: as above
	}
	return false; // RA2: as above
}
