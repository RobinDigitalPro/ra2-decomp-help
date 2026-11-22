// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004064A0 (127 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x64b0 (VA 0x004064B0, 128 bytes incl. padding)
// RA2 symbol : ?AudioEventTypeAddSample@@YIHPAVAudioEventType@@PBD@Z
// similarity : 0.9778 (very-similar, masked instruction tokens; shape 0.9890)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Adds a sample of the bag to an event type; a missing sample is logged and clears SamplesOK.
/// </summary>
int __fastcall AudioEventTypeAddSample(AudioEventType * type, char const * sample) // RA2: 0x004064B0
{
	int index; // RA2: as above

	if (type->NumSamples == MAX_AUDIO_EVENT_SAMPLES) { // RA2: as above
		return 0; // RA2: as above
	}
	if (audioEventsReady && AudioIDXData::Instance) { // RA2: as above
		while (*sample == '$' || *sample == '#') { // RA2: as above
			sample++; // RA2: as above
		}
		index = AudioIDXData::Instance->FindSampleIndex(sample); // RA2: as above
		if (index != -1) { // RA2: as above
			type->SampleIndex[type->NumSamples] = index; // RA2: as above
			type->NumSamples++; // RA2: as above
			return 1; // RA2: as above
		}
		DebugString("Missing sample %s\n", sample); // RA2: as above
		type->SamplesOK = 0; // RA2: as above
	}
	return 1; // RA2: as above
}
