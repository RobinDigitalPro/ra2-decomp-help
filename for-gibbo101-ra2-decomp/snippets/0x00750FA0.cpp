// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00750FA0 (77 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x308fd0 (VA 0x00708FD0, 80 bytes incl. padding)
// RA2 symbol : ?Sound_Clear_Static@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9455)
// source TU  : src/m85/src/voc.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Stops every static sound and drops it from the list.
/// </summary>
void Sound_Clear_Static(void) // RA2: empties the static sound list
{
	VocStaticSound * sound = (VocStaticSound *)ListFirstItem(&StaticSounds); // RA2: as above
	while (sound != NULL) { // RA2: as above
		VocStaticSound * next = (VocStaticSound *)ListNextItem(sound); // RA2: as above
		sound->Controller.Stop(); // RA2: as above
		ListNodeRemove(sound); // RA2: as above
		MemoryPoolReturnItem(StaticSoundPool, sound); // RA2: as above
		StaticSoundCount--; // RA2: as above
		sound = next; // RA2: as above
	}
}
