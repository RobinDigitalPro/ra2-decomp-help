// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00751080 (76 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x3090b0 (VA 0x007090B0, 80 bytes incl. padding)
// RA2 symbol : ?Sound_Resume_All@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9333)
// source TU  : src/m85/src/voc.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Resumes every static sound.
/// </summary>
void Sound_Resume_All(void) // RA2: resumes the static sounds
{
	for (VocStaticSound * sound = (VocStaticSound *)ListFirstItem(&StaticSounds); sound != NULL; sound = (VocStaticSound *)ListNextItem(sound)) { // RA2: as above
		sound->Resume(); // RA2: as above
	}
}
