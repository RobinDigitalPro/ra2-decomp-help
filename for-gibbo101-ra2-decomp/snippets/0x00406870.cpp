// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00406870 (98 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x6880 (VA 0x00406880, 112 bytes incl. padding)
// RA2 symbol : ?AudioTypeApplyKeyword@@YIHPAIPBD@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8654)
// source TU  : src/m85/src/audevent.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Adds the type flag of a name to the flags (a SCREEN, LOCAL or GLOBAL replaces the others of its kind, as UNSHROUD and SHROUD do);
/// returns whether the name is one.
/// </summary>
int __fastcall AudioTypeApplyKeyword(unsigned int * type, char const * name) // RA2: 0x00406880
{
	EventKeyword * entry; // RA2: as above

	for (entry = TypeKeywords; entry->Name; entry++) { // RA2: as above
		if (!stricmp(name, entry->Name)) { // RA2: as above
			break; // RA2: as above
		}
	}
	if (type) { // RA2: as above
		if (entry->Value & 0x60) { // RA2: as above
			*type &= ~0x60;
		} else if (entry->Value & 0xC00) { // RA2: as above
			*type &= ~0xC00;
		}
		*type |= entry->Value;
	}
	return entry->Name != NULL; // RA2: as above
}
