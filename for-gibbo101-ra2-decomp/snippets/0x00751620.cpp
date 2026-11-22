// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00751620 (233 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x309650 (VA 0x00709650, 240 bytes incl. padding)
// RA2 symbol : ?Static_Sounds_Save@@YIJPAUIStream@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9605)
// source TU  : src/m85/src/voc.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Saves the static sounds: how many there are, then the sound effect number and the location
/// of each in the order of the list.
/// </summary>
/// <param name="stream">The stream to save to.</param>
HRESULT __fastcall Static_Sounds_Save(IStream * stream) // RA2: the static sounds are saved with the game
{
	int count = ListCountItems(&StaticSounds); // RA2: as above
	HRESULT result = stream->Write(&count, sizeof(count), 0); // RA2: as above
	if (SUCCEEDED(result)) { // RA2: as above
		VocStaticSound * sound = (VocStaticSound *)ListFirstItem(&StaticSounds); // RA2: as above
		while (sound) { // RA2: as above
			struct { // RA2: as above
				int Index; // RA2: as above
				int X; // RA2: the location, as three words
				int Y; // RA2: as above
				int Z; // RA2: as above
			} entry; // RA2: as above
			int index = -1; // RA2: as above
			entry.Index = index; // RA2: as above
			if (sound->Controller.EventType) { // RA2: as above
				char const * name = AudioEventTypeName((AudioEventType *)sound->Controller.EventType); // RA2: as above
				if (name) { // RA2: as above
					index = VocClass::From_Name(name); // RA2: as above
				}
				entry.Index = index; // RA2: as above
			}
			entry.X = sound->Position.X; // RA2: as above
			entry.Y = sound->Position.Y; // RA2: as above
			entry.Z = sound->Position.Z; // RA2: as above
			result = stream->Write(&entry, sizeof(entry), 0); // RA2: as above
			if (FAILED(result)) { // RA2: as above
				return(result); // RA2: as above
			}
			sound = (VocStaticSound *)ListNextItem(sound); // RA2: as above
		}
	}
	return(result); // RA2: as above
}
