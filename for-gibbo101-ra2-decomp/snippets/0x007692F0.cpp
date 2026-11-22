// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007692F0 (61 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31f1e0 (VA 0x0071F1E0, 64 bytes incl. padding)
// RA2 symbol : ?Start_Intro@Map@WorldDominationTour@@QAEXPAVMSEngine@@PAVVoices@2@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9388)
// source TU  : src/m85/src/wdtmap.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: with an opening movie, says the first voice list and waits for the movie (at most 300000 ms); then shows the background.
/// </summary>
void Map::Start_Intro(MSEngine * engine, Voices * voices) // RA2: with an opening movie, says the first voice list and waits for the movie (at most 300000 ms); then shows the background
{
	if (OpeningAnim) { // RA2: as above
		voices->Say_List(0, true, 0); // RA2: as above
		engine->Wait_For_Anim(OpeningAnim, 300000); // RA2: as above
	}
	if (BackgroundAnim) { // RA2: as above
		BackgroundAnim->Set_Active(true); // RA2: as above
	}
}
