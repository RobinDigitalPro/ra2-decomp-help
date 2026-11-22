// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0053E550 (155 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1221f0 (VA 0x005221F0, 160 bytes incl. padding)
// RA2 symbol : ?Audio_File_Open_Stream@@YIHPBD@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9412)
// source TU  : src/m85/src/audfile.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Opens a recording ("rb"), fills the ring buffer from it and switches to playing back.
/// </summary>
int __fastcall Audio_File_Open_Stream(char const * name) // RA2: 0x00522CB0
{
	if (AudioFileReady && AudioFileStream == NULL) { // RA2: as above
		EnterCriticalSection(&AudioFileLock); // RA2: as above
		AudioFileStream = fopen(name, "rb"); // RA2: as above
		AudioFileFillFailed = 0; // RA2: as above
		if (AudioFileStream != NULL) { // RA2: as above
			AudioFileMode = 2; // RA2: as above
			if (STM_AccessCRTFileTransfer(AudioFileReadQueue, AudioFileStream, STM_AccessTotalBytes(AudioFileReadQueue), NULL) != STM_OK) { // RA2: as above
				AudioFileFillFailed = 1; // RA2: as above
			}
		}
		LeaveCriticalSection(&AudioFileLock); // RA2: as above
		return AudioFileStream != NULL; // RA2: as above
	}
	return false; // RA2: as above
}
