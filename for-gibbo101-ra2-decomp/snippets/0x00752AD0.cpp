// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00752AD0 (99 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x30aad0 (VA 0x0070AAD0, 112 bytes incl. padding)
// RA2 symbol : ?Aux_Stream_Init@@YIHXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7869)
// source TU  : src/m85/src/vox.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int Aux_Stream_Init(void) // RA2: 0x00715F10; makes the "Taunt Stream" stream (0 without one)
{
	if (AuxStream == 0) { // RA2: as above
		AuxStream = AudioStreamerCreate(AudioGetDevice(), 3000); // RA2: as above
		if (AuxStream == 0) { // RA2: as above
			return(0); // RA2: as above
		}
	}
	AudioStreamerSetName(AuxStream, "Taunt Stream"); // RA2: as above
	AudioStreamerSetAttribs(SpeechStream, AudioVoiceAttribs); // RA2: as above
	AudioStreamerSetFadeAttribs(SpeechStream, AudioGroupAttribs2); // RA2: as above
	AuxStreamHold = 0; // RA2: as above
	return(1); // RA2: as above
}
