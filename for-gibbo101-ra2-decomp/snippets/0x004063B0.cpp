// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004063B0 (226 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x63c0 (VA 0x004063C0, 240 bytes incl. padding)
// RA2 symbol : ?AudioEventTypeFind@@YIPAVAudioEventType@@PBD@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9114)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// The event type of this name; a new one with the defaults is made when there is none.
/// </summary>
AudioEventType * __fastcall AudioEventTypeFind(char const * name) // RA2: 0x004063C0
{
	AudioEventType * eclass; // RA2: as above

	if (!audioEventsReady) { // RA2: as above
		return NULL; // RA2: as above
	}
	eclass = (AudioEventType *)ListFirstItem(&audioEventClasses); // RA2: as above
	while (eclass) { // RA2: as above
		if (!stricmp(name, eclass->Name)) { // RA2: as above
			break; // RA2: as above
		}
		eclass = (AudioEventType *)ListNextItem(&eclass->Header); // RA2: as above
	}
	if (eclass) { // RA2: as above
		return eclass; // RA2: as above
	}
	eclass = new AudioEventType; // RA2: as above
	memset(eclass, 0, sizeof(AudioEventType)); // RA2: as above
	memset(eclass, 0, sizeof(AudioEventType)); // RA2: as above
	ListNodeInit(&eclass->Header); // RA2: as above
	eclass->SamplesOK = 1; // RA2: as above
	eclass->Control = 0; // RA2: as above
	eclass->Type = 0x20; // RA2: as above
	eclass->Limit = 3; // RA2: as above
	eclass->Priority = 2; // RA2: as above
	eclass->Range = 10; // RA2: as above
	eclass->MinVolume = 0.2f; // RA2: as above
	AudioLevelInit(&eclass->Volume, AUDIO_LEVEL_MAX); // RA2: as above
	strncpy(eclass->Name, name, 31); // RA2: as above
	eclass->Name[31] = 0; // RA2: as above
	ListNodeInsert((ListNode *)&audioEventClasses, &eclass->Header); // RA2: as above
	return eclass; // RA2: as above
}
