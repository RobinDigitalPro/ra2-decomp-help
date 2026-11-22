// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006CA6A0 (130 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x291500 (VA 0x00691500, 144 bytes incl. padding)
// RA2 symbol : ?Parse_Position@@YIXPAGPAVSubTitle@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8871)
// source TU  : src/m85/src/subtitle2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: Position=: the line (optional, before a colon) and the alignment (Left, Right or Center).
/// </summary>
void __fastcall Parse_Position(wchar_t * value, SubTitle * subtitle) // RA2: 0x0069BE60
{
	wchar_t * colon = wcschr(value, L':'); // RA2: as above
	if (colon != NULL) { // RA2: as above
		*colon = 0; // RA2: as above
		subtitle->Set_Line_Position(wcstol(value, NULL, 0)); // RA2: as above
		value = colon + 1; // RA2: as above
	}

	int alignment = SubTitle::Center; // RA2: as above
	for (int i = 0; SubtitleAlignments[i].Name != NULL; i++) { // RA2: as above
		if (_wcsicmp(value, SubtitleAlignments[i].Name) == 0) { // RA2: as above
			alignment = SubtitleAlignments[i].Value; // RA2: as above
			break; // RA2: as above
		}
	}
	subtitle->Set_Alignment((SubTitle::Alignment)alignment); // RA2: as above
}
