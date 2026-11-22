// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00752680 (126 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x30a680 (VA 0x0070A680, 128 bytes incl. padding)
// RA2 symbol : ?Speech_Find@@YIPAUVoxSpeech@@PAVVoxClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9787)
// source TU  : src/m85/src/vox.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

VoxSpeech *__fastcall Speech_Find(VoxClass *vox) // RA2: 0x00715AC0; the waiting speech of a VoxClass: the critical list, the pending speech, the queue lists from critical down, then the queued interrupts
{
	VoxSpeech *speech; // RA2: as above
	for (speech = (VoxSpeech *)ListFirstItem(&SpeechUrgentList); speech != 0; // RA2: as above
			speech = (VoxSpeech *)ListNextItem(speech)) { // RA2: as above
		if (speech->Vox == vox) { // RA2: as above
			return speech; // RA2: as above
		}
	}
	if (SpeechPending != 0 && SpeechPending->Vox == vox) { // RA2: as above
		return SpeechPending; // RA2: as above
	}
	for (int priority = 3; priority >= 0; priority--) { // RA2: as above
		for (speech = (VoxSpeech *)ListFirstItem(&SpeechLists[priority]); speech != 0; // RA2: as above
				speech = (VoxSpeech *)ListNextItem(speech)) { // RA2: as above
			if (speech->Vox == vox) { // RA2: as above
				return speech; // RA2: as above
			}
		}
	}
	for (speech = (VoxSpeech *)ListFirstItem(&SpeechQueuedList); speech != 0; // RA2: as above
			speech = (VoxSpeech *)ListNextItem(speech)) { // RA2: as above
		if (speech->Vox == vox) { // RA2: as above
			return speech; // RA2: as above
		}
	}
	return(0); // RA2: as above
}
