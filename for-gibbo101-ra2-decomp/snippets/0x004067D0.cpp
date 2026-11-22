// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004067D0 (69 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x67e0 (VA 0x004067E0, 80 bytes incl. padding)
// RA2 symbol : ?AudioPriorityFromName@@YI_NPBDPAH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8533)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// The priority of a name (LOWEST to CRITICAL); returns whether the name is one.
/// </summary>
bool __fastcall AudioPriorityFromName(char const * name, int * priority) // RA2: 0x004067E0
{
	EventKeyword * entry; // RA2: as above

	for (entry = PriorityKeywords; entry->Name; entry++) { // RA2: as above
		if (!stricmp(name, entry->Name)) { // RA2: as above
			break; // RA2: as above
		}
	}
	if (priority) { // RA2: as above
		*priority = entry->Value;
	}
	return entry->Name != NULL; // RA2: as above
}
