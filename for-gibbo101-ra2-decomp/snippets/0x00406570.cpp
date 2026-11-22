// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00406570 (76 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x6580 (VA 0x00406580, 80 bytes incl. padding)
// RA2 symbol : ?AudioEventTypeSetControl@@YIXPAVAudioEventType@@I@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9130)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Sets the control flags of an event type; an attack or decay sample is needed when its flag is set and none when it is not.
/// </summary>
void __fastcall AudioEventTypeSetControl(AudioEventType * type, unsigned int control) // RA2: 0x00406580
{
	type->Control = control; // RA2: as above
	if (control & AUDIO_EVENT_CTRL_ATTACK) { // RA2: as above
		if (type->Attack == 0) { // RA2: as above
			type->Attack = 1; // RA2: as above
		}
	} else { // RA2: as above
		type->Attack = 0; // RA2: as above
	}
	if (control & AUDIO_EVENT_CTRL_DECAY) { // RA2: as above
		if (type->Decay == 0) { // RA2: as above
			type->Decay = 1; // RA2: as above
		}
	} else { // RA2: as above
		type->Decay = 0; // RA2: as above
	}
}
