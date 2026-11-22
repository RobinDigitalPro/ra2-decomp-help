// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00752290 (174 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x30a290 (VA 0x0070A290, 176 bytes incl. padding)
// RA2 symbol : ?Speech_Init@@YIHXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9750)
// source TU  : src/m85/src/vox.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int Speech_Init(void) // RA2: 0x007156D0; empties the speech lists and makes the "EVA Stream" stream on the voice and group attributes (0 without a stream)
{
	SpeechHold = 0; // RA2: as above
	SpeechSuspend = 0; // RA2: as above
	for (int i = 0; i < 4; i++) { // RA2: as above
		ListInit(&SpeechLists[i]); // RA2: as above
	}
	ListInit(&SpeechUrgentList); // RA2: as above
	ListInit(&SpeechQueuedList); // RA2: as above
	SpeechPending = 0; // RA2: as above
	SpeechEnabled = 1; // RA2: as above
	if (SpeechStream == 0) { // RA2: as above
		SpeechStream = AudioStreamerCreate(AudioGetDevice(), 3000); // RA2: as above
		if (SpeechStream == 0) { // RA2: as above
			return(0); // RA2: as above
		}
	}
	AudioStreamerSetName(SpeechStream, "EVA Stream"); // RA2: as above
	AudioStreamerSetAttribs(SpeechStream, AudioVoiceAttribs); // RA2: as above
	AudioStreamerSetFadeAttribs(SpeechStream, AudioGroupAttribs2); // RA2: as above
	return(1); // RA2: as above
}
