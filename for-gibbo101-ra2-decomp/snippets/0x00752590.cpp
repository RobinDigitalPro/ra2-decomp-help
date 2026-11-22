// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00752590 (227 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x30a590 (VA 0x0070A590, 240 bytes incl. padding)
// RA2 symbol : ?Speech_Enqueue@@YIXPAVVoxClass@@HH@Z
// similarity : 0.9750 (very-similar, masked instruction tokens; shape 0.9249)
// source TU  : src/m85/src/vox.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Speech_Enqueue(VoxClass *vox, int type, int priority) // RA2: 0x007159D0; makes a waiting speech: queued interrupts and the queue lists by priority and critical ones wait, any other is kept as the one pending speech when nothing else waits and it outranks the pending one, else dropped
{
	VoxSpeech *speech = new VoxSpeech; // RA2: as above
	ListNodeInit(speech); // RA2: as above
	speech->Vox = vox; // RA2: as above
	speech->Priority = priority; // RA2: as above
	speech->Type = type; // RA2: as above
	speech->Serial = SpeechSerial % 100; // RA2: as above
	SpeechSerial++; // RA2: as above
	vox->State = 1; // RA2: as above
	if (type == 3) { // RA2: as above
		ListNodeInsert(&SpeechQueuedList, speech); // RA2: as above
	} else if (type == 1) { // RA2: as above
		ListNodeInsert(&SpeechLists[priority], speech); // RA2: as above
	} else if (priority == 3) { // RA2: as above
		ListNodeInsert(&SpeechUrgentList, speech); // RA2: as above
	} else if (SpeechQueuedList.prev == &SpeechQueuedList // RA2: as above
			&& SpeechUrgentList.prev == &SpeechUrgentList // RA2: as above
			&& (SpeechPending == 0 || SpeechPending->Priority < priority)) { // RA2: as above
		SpeechPending = speech; // RA2: as above
	} else {
		vox->State = 2; // RA2: as above
		delete speech; // RA2: as above
	}
}
