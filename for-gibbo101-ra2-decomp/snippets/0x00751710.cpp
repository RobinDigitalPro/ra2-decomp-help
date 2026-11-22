// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00751710 (397 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x309740 (VA 0x00709740, 400 bytes incl. padding)
// RA2 symbol : ?Static_Sounds_Load@@YIJPAUIStream@@@Z
// similarity : 0.9917 (very-similar, masked instruction tokens; shape 0.9878)
// source TU  : src/m85/src/voc.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Loads the static sounds. Every sound is dropped first, then each saved sound whose sound
/// effect loops forever is started again at its location.
/// </summary>
/// <param name="stream">The stream to load from.</param>
long __fastcall Static_Sounds_Load(IStream * stream) // RA2: the static sounds are loaded with the game
{
	Sound_Clear_Static(); // RA2: as above
	Audio_Stop_Events(); // RA2: as above
	int count; // RA2: as above
	HRESULT result = stream->Read(&count, sizeof(count), 0); // RA2: as above
	if (SUCCEEDED(result)) { // RA2: as above
		for (int index = 0; index < count; index++) { // RA2: as above
			struct { // RA2: as above
				int Index; // RA2: as above
				int X; // RA2: the location, as three words
				int Y; // RA2: as above
				int Z; // RA2: as above
			} entry; // RA2: as above
			result = stream->Read(&entry, sizeof(entry), 0); // RA2: as above
			if (FAILED(result)) { // RA2: as above
				return(result); // RA2: as above
			}
			if (entry.Index != -1 && entry.Index < Vocs.Count() && entry.Index >= 0) { // RA2: as above
				VocClass * voc = Vocs[entry.Index]; // RA2: as above
				if (voc->Event != NULL && AudioEventTypeLoopsForever(voc->Event)) { // RA2: as above
					Coord position; // RA2: as above
					position.X = entry.X; // RA2: as above
					position.Y = entry.Y; // RA2: as above
					position.Z = entry.Z; // RA2: as above
					VocClass::PlayIndexAtPos(entry.Index, position, 0); // RA2: as above
				}
			}
		}
	}
	return(result); // RA2: as above
}
