// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00750EC0 (118 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x308ef0 (VA 0x00708EF0, 128 bytes incl. padding)
// RA2 symbol : ?Sound_Service@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8958)
// source TU  : src/m85/src/voc.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Updates every static sound that is not paused and drops the ones whose event has ended.
/// A sound that loops forever is kept, so that it can start again when it comes into hearing.
/// </summary>
void Sound_Service(void) // RA2: services the static sounds
{
	VocStaticSound * sound = (VocStaticSound *)ListFirstItem(&StaticSounds); // RA2: as above
	while (sound != NULL) { // RA2: as above
		VocStaticSound * next = (VocStaticSound *)ListNextItem(sound); // RA2: as above
		if (sound->PauseCount == 0) { // RA2: as above
			VocClass::UpdateAt(sound->Position, &sound->Controller); // RA2: as above
		}
		if (AudioControllerGetEvent(&sound->Controller) == NULL) { // RA2: as above
			AudioEventType * type = AudioControllerGetType(&sound->Controller); // RA2: as above
			if (type == NULL || !AudioEventTypeLoopsForever(type)) { // RA2: as above
				ListNodeRemove(sound); // RA2: as above
				MemoryPoolReturnItem(StaticSoundPool, sound); // RA2: as above
				StaticSoundCount--; // RA2: as above
			}
		}
		sound = next; // RA2: as above
	}
}
