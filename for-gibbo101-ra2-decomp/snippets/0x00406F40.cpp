// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00406F40 (41 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x6e70 (VA 0x00406E70, 48 bytes incl. padding)
// RA2 symbol : ?Audio_Resume_All@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7407)
// source TU  : src/m85/src/audio.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Audio_Resume_All(void)
{
	Aux_Stream_Resume();
	Theme_Resume();
	Sound_Resume_All();
	AudioResumeAllEvents();
	if (AudioMainDevice) {
		AudioDeviceResumeAllChannels(AudioMainDevice, 1);
	}
}
