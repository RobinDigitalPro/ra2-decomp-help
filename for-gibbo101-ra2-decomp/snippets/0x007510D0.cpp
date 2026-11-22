// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007510D0 (791 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x309100 (VA 0x00709100, 800 bytes incl. padding)
// RA2 symbol : ?Init_Vocs@@YIXAAVCCINIClass@@@Z
// similarity : 0.9910 (very-similar, masked instruction tokens; shape 0.9800)
// source TU  : src/m85/src/voc.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Creates the master sound effect list from the rules.
/// This routine will fetch every sound named in the sound list section, creating a sound
/// effect for any that does not exist yet, and then let each one fill itself in from its
/// own section.
/// </summary>
/// <param name="ini">The rules database to fetch the sound list from.</param>
void Init_Vocs(CCINIClass &ini) // RA2: the rules are read through a non-const reference, and the defaults come with them
{
	char const * const SECTION = "SoundList";

	ListInit(&StaticSounds); // RA2: the static sounds start out empty, in a pool of 100
	StaticSoundPool = MemoryPoolCreate(100, sizeof(VocStaticSound)); // RA2: as above
	StaticSoundCount = 0; // RA2: as above
	StaticSoundMaximum = 0; // RA2: as above

	char buffer[0x800]; // RA2: as above
	char * token; // RA2: as above
	if (ini.Is_Present("Defaults")) { // RA2: as above
		DefaultVolume = (float)ini.Get_Float("Defaults", "Volume", DefaultVolume); // RA2: as above
		DefaultMinVolume = (float)ini.Get_Float("Defaults", "MinVolume", DefaultMinVolume); // RA2: as above
		ini.Get_String("Defaults", "Priority", "NORMAL", buffer, sizeof(buffer)); // RA2: as above
		AudioPriorityFromName(buffer, &DefaultPriority); // RA2: as above

		ini.Get_String("Defaults", "Control", "", buffer, sizeof(buffer)); // RA2: as above
		token = strtok(buffer, " \t\n"); // RA2: as above
		if (token != NULL) { // RA2: as above
			DefaultControl = 0; // RA2: as above
			do { // RA2: as above
				AudioControlApplyKeyword(&DefaultControl, token); // RA2: as above
				token = strtok(NULL, " \t\n"); // RA2: as above
			} while (token != NULL); // RA2: as above
		}

		ini.Get_String("Defaults", "Type", "", buffer, sizeof(buffer)); // RA2: as above
		token = strtok(buffer, " \t\n"); // RA2: as above
		if (token != NULL) { // RA2: as above
			DefaultType = 0x20; // RA2: as above
			do { // RA2: as above
				AudioTypeApplyKeyword(&DefaultType, token); // RA2: as above
				token = strtok(NULL, " \t\n"); // RA2: as above
			} while (token != NULL); // RA2: as above
		}

		DefaultLimit = ini.Get_Int("Defaults", "Limit", DefaultLimit); // RA2: as above
		DefaultRange = ini.Get_Int("Defaults", "Range", DefaultRange); // RA2: as above
	}

	if (ini.Is_Present(SECTION)) {
		int count = ini.Entry_Count(SECTION);
		for (int i = 0; i < count; i++) {
			char name[32];
			if (ini.Get_String(SECTION, ini.Get_Entry(SECTION, i), "", name, sizeof(name)) != 0) {

				VocClass *voc = NULL;
				VocType type = VocClass::From_Name(name);
				if (type == VOC_NONE) {
					voc = new VocClass(name);
				} else {
					voc = Vocs[type];
				}
				voc->Fill_In(ini);
			}
		}
	}
}
