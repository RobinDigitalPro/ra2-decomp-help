// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007533F0 (229 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x30b390 (VA 0x0070B390, 240 bytes incl. padding)
// RA2 symbol : ?Speech_Load@@YIJPAUIStream@@@Z
// similarity : 0.9870 (very-similar, masked instruction tokens; shape 0.9333)
// source TU  : src/m85/src/vox.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

long __fastcall Speech_Load(IStream *stream) // RA2: 0x007167D0; stops the speech, then queues the speeches a saved game lists between the SxoV and ExoV markers (IxoV, the VoxClass index, type and priority)
{
	Speech_Stop(true); // RA2: as above
	int marker; // RA2: as above
	HRESULT result = stream->Read(&marker, sizeof(marker), 0); // RA2: as above
	if (FAILED(result) || marker != 0x566F7853) { // RA2: as above
		return result; // RA2: as above
	}
	for (result = stream->Read(&marker, sizeof(marker), 0); SUCCEEDED(result); // RA2: as above
			result = stream->Read(&marker, sizeof(marker), 0)) { // RA2: as above
		if (marker == 0x566F7845) { // RA2: as above
			break;
		}
		if (marker != 0x566F7849) { // RA2: as above
			return (HRESULT)0x80004005L; // RA2: as above
		}
		struct { // RA2: as above
			int Index; // RA2: as above
			int Type; // RA2: as above
			int Priority; // RA2: as above
		} entry; // RA2: as above
		result = stream->Read(&entry, sizeof(entry), 0); // RA2: as above
		if (FAILED(result)) { // RA2: as above
			break;
		}
		if (SpeechStream != 0 && entry.Index >= 0 && entry.Index < Voxs.Count()) { // RA2: as above
			Speech_Enqueue(Voxs[entry.Index], entry.Type, entry.Priority); // RA2: as above
		}
	}
	return result; // RA2: as above
}
