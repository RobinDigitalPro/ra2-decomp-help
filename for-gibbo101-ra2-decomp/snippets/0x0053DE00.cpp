// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0053DE00 (609 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x121aa0 (VA 0x00521AA0, 624 bytes incl. padding)
// RA2 symbol : ?Audio_File_Init@@YIHHH@Z
// similarity : 0.9834 (very-similar, masked instruction tokens; shape 0.9602)
// source TU  : src/m85/src/audfile.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Sets the recorder up: the two critical sections, the window table (count entries), the streamer thread, and the
/// ring buffer (at least 0x2800 bytes) with its two queues. Any failure shuts it down again and returns 0.
/// </summary>
int __fastcall Audio_File_Init(int count, int size) // RA2: 0x00522560
{
	InitializeCriticalSection(&AudioFileLock); // RA2: as above
	InitializeCriticalSection(&AudioFileCursorLock); // RA2: as above
	AudioFileLocksReady = 1; // RA2: as above

	if (count <= 0) { // RA2: as above
		Audio_File_Shutdown(); // RA2: as above
		return 0; // RA2: as above
	}
	if (size < 0x2800) { // RA2: as above
		size = 0x2800; // RA2: the ring buffer is never smaller
	}

	AudioFileWindows = (HWND *)operator new(count * sizeof(HWND)); // RA2: as above
	if (AudioFileWindows == NULL) { // RA2: as above
		Audio_File_Shutdown(); // RA2: as above
		return 0; // RA2: as above
	}
	memset(AudioFileWindows, 0, count * sizeof(HWND)); // RA2: as above
	AudioFileWindowCount = 0; // RA2: as above
	AudioFileWindowSlots = count; // RA2: as above

	AudioFileThread.Stop = 0; // RA2: as above
	AudioFileThread.Stopped = 0; // RA2: as above
	AudioFileThread.Running = 0; // RA2: as above
	AudioFileThread.Period = 100; // RA2: as above
	AudioFileThread.Passes = 0; // RA2: as above
	AudioServiceInfoInit(&AudioFileThread.Timing); // RA2: as above
	AudioServiceSetInterval(&AudioFileThread.Timing, AudioFileThread.Period); // RA2: as above
	AudioServiceSetMustServiceInterval(&AudioFileThread.Timing, AudioFileThread.Period * 4); // RA2: as above
	AudioServiceSetResetInterval(&AudioFileThread.Timing, AudioFileThread.Period * 4); // RA2: as above

	AudioFileThreadHandle = CreateThread(NULL, 0x1000, Audio_File_Thread, &AudioFileThread, 0, &AudioFileThreadId); // RA2: as above
	if (AudioFileThreadHandle == NULL) { // RA2: as above
		Audio_File_Shutdown(); // RA2: as above
		return 0; // RA2: as above
	}
	AudioFileThreadRunning = 1; // RA2: as above

	if (!SetThreadPriority(AudioFileThreadHandle, THREAD_PRIORITY_HIGHEST)) { // RA2: as above
		char buffer[1024]; // RA2: as above
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 0, buffer, sizeof(buffer), NULL); // RA2: as above
		DebugString("Unable to change the priority of the Streamer Thread - %s\n", buffer); // RA2: as above
		Audio_File_Shutdown(); // RA2: as above
		return 0; // RA2: as above
	}

	AudioFileRing = STM_StreamCreate(); // RA2: as above
	if (AudioFileRing == NULL) { // RA2: as above
		Audio_File_Shutdown(); // RA2: as above
		return 0; // RA2: as above
	}
	if (!STM_StreamCreateSBuffers(AudioFileRing, 1, size, 0)) { // RA2: as above
		Audio_File_Shutdown(); // RA2: as above
		return 0; // RA2: as above
	}
	STM_StreamReset(AudioFileRing); // RA2: as above
	AudioFileReadQueue = STM_StreamAcquireAccess(AudioFileRing, vSTM_ACCESS_ID_IN); // RA2: as above
	AudioFileFlushQueue = STM_StreamAcquireAccess(AudioFileRing, vSTM_ACCESS_ID_OUT); // RA2: as above
	if (AudioFileReadQueue == NULL || AudioFileFlushQueue == NULL) { // RA2: as above
		Audio_File_Shutdown(); // RA2: as above
		return 0; // RA2: as above
	}

	AudioFileReady = 1; // RA2: as above
	memset(KeyStates, 0, sizeof(KeyStates)); // RA2: as above
	Add_Audio_File_Window(MainWindow); // RA2: the main window is window number 0 of the recording
	return 1; // RA2: as above
}
