// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0053E070 (344 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x121d10 (VA 0x00521D10, 352 bytes incl. padding)
// RA2 symbol : ?Audio_File_Thread@@YGKPAX@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9626)
// source TU  : src/m85/src/audfile.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// The streamer thread: every Period milliseconds it either tops the ring buffer up from the file (playing back) or
/// writes half of it out to the file (recording), until it is asked to stop.
/// </summary>
DWORD WINAPI Audio_File_Thread(void * data) // RA2: 0x005227D0
{
	AudioFileThreadInfo * info = (AudioFileThreadInfo *)data; // RA2: as above

	info->Running = 1; // RA2: as above
	info->Stopped = 0; // RA2: as above
	while (!info->Stop) { // RA2: as above
		AudioServicePerform(&info->Timing, AudioGetTime()); // RA2: as above

		STM_STREAM * ring = AudioFileRing; // RA2: as above
		if (AudioFileRing != NULL && AudioFileMode != 0 && AudioFileStream != NULL) { // RA2: as above
			EnterCriticalSection(&AudioFileLock); // RA2: as above
			if (AudioFileMode == 2 && STM_StreamTotalBytesIn(ring) < (unsigned)STM_StreamTotalBytes(ring) >> 1) { // RA2: as above
				if (AudioFileReadQueue != NULL) { // RA2: as above
					int done; // RA2: as above
					if (STM_AccessCRTFileTransfer(AudioFileReadQueue, AudioFileStream, STM_StreamTotalBytesTillFull(ring), &done) != STM_OK) { // RA2: as above
						AudioFileFillFailed = 1; // RA2: a short read: the file is at its end
					}
				}
			} else if (AudioFileMode == 1 && STM_StreamTotalBytesTillFull(ring) < (unsigned)STM_StreamTotalBytes(ring) >> 1 && AudioFileFlushQueue != NULL) { // RA2: as above
				STM_AccessCRTFileTransfer(AudioFileFlushQueue, AudioFileStream, (unsigned)STM_StreamTotalBytes(ring) >> 1, NULL); // RA2: as above
				fflush(AudioFileStream); // RA2: as above
			}
			LeaveCriticalSection(&AudioFileLock); // RA2: as above
		}

		Sleep((DWORD)info->Period); // RA2: as above
		info->Passes++; // RA2: as above
	}
	info->Stopped = 1; // RA2: as above
	return 0; // RA2: as above
}
