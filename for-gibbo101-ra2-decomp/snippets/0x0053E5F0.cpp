// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0053E5F0 (181 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x122290 (VA 0x00522290, 192 bytes incl. padding)
// RA2 symbol : ?Audio_File_Close_Stream@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9009)
// source TU  : src/m85/src/audfile.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Flushes and closes the file and switches the recorder off.
/// </summary>
void __fastcall Audio_File_Close_Stream(void) // RA2: 0x00522D50
{
	if (AudioFileReady) { // RA2: as above
		EnterCriticalSection(&AudioFileLock); // RA2: as above
		Audio_File_Flush(); // RA2: as above
		AudioFileMode = 0; // RA2: as above
		if (AudioFileStream != NULL) { // RA2: as above
			fclose(AudioFileStream); // RA2: as above
			AudioFileStream = NULL; // RA2: as above
		}
		LeaveCriticalSection(&AudioFileLock); // RA2: as above
	}
}
