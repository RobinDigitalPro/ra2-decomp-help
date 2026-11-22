// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00752340 (42 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x30a340 (VA 0x0070A340, 48 bytes incl. padding)
// RA2 symbol : ?Speech_Shutdown@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7500)
// source TU  : src/m85/src/vox.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Speech_Shutdown(void) // RA2: 0x00715780; drops the waiting speeches, then stops and destroys the stream
{
	Flush_Speech(); // RA2: as above
	if (SpeechStream != 0) { // RA2: as above
		AudioStreamerStop(SpeechStream); // RA2: as above
		AudioStreamerDestroy(SpeechStream); // RA2: as above
		SpeechStream = 0; // RA2: as above
	}
}
