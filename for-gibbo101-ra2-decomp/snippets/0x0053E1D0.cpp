// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0053E1D0 (488 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x121e70 (VA 0x00521E70, 496 bytes incl. padding)
// RA2 symbol : ?Audio_File_Shutdown@@YIXXZ
// similarity : 0.9766 (very-similar, masked instruction tokens; shape 0.9697)
// source TU  : src/m85/src/audfile.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Closes the recorder: flushes and closes the file, stops the thread, frees the window table, the queues, the ring
/// and the critical sections.
/// </summary>
void __fastcall Audio_File_Shutdown(void) // RA2: 0x00522930
{
	if (AudioFileReady) { // RA2: as above
		Audio_File_Flush(); // RA2: as above
		Audio_File_Close_Stream(); // RA2: as above
	}

	if (AudioFileWindows != NULL) { // RA2: as above
		delete [] AudioFileWindows; // RA2: as above
		AudioFileWindows = NULL; // RA2: as above
	}
	AudioFileWindowCount = 0; // RA2: as above

	if (AudioFileThreadRunning) { // RA2: as above
		AudioFileThread.Stop = 1; // RA2: as above
		while (!AudioFileThread.Stopped) { // RA2: as above
			Sleep(0); // RA2: waits for the thread to see the flag
		}
		WaitForSingleObject(AudioFileThreadHandle, 5000); // RA2: as above
		CloseHandle(AudioFileThreadHandle); // RA2: as above
		AudioFileThreadRunning = 0; // RA2: as above
	}

	if (AudioFileReadQueue != NULL) { // RA2: as above
		STM_AccessRelease(AudioFileReadQueue); // RA2: as above
		AudioFileReadQueue = NULL; // RA2: as above
	}
	if (AudioFileFlushQueue != NULL) { // RA2: as above
		STM_AccessRelease(AudioFileFlushQueue); // RA2: as above
		AudioFileFlushQueue = NULL; // RA2: as above
	}
	if (AudioFileRing != NULL) { // RA2: as above
		STM_StreamDestroy(AudioFileRing); // RA2: as above
		AudioFileRing = NULL; // RA2: as above
	}

	if (AudioFileLocksReady) { // RA2: as above
		DeleteCriticalSection(&AudioFileLock); // RA2: as above
		DeleteCriticalSection(&AudioFileCursorLock); // RA2: as above
		AudioFileLocksReady = 0; // RA2: as above
	}
	AudioFileReady = 0; // RA2: as above
}
