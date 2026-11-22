// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00406820 (73 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x6830 (VA 0x00406830, 80 bytes incl. padding)
// RA2 symbol : ?AudioControlApplyKeyword@@YI_NPAIPBD@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9067)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Adds the control flag of a name to the flags; returns whether the name is one.
/// </summary>
bool __fastcall AudioControlApplyKeyword(unsigned int * control, char const * name) // RA2: 0x00406830
{
	EventKeyword * entry; // RA2: as above

	for (entry = ControlKeywords; entry->Name; entry++) { // RA2: as above
		if (!stricmp(name, entry->Name)) { // RA2: as above
			break; // RA2: as above
		}
	}
	if (control) { // RA2: as above
		*control |= entry->Value;
	}
	return entry->Name != NULL; // RA2: as above
}
