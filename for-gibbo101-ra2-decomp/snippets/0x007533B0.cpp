// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007533B0 (57 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x30b350 (VA 0x0070B350, 64 bytes incl. padding)
// RA2 symbol : ?Speech_Save@@YIJPAUIStream@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8727)
// source TU  : src/m85/src/vox.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

HRESULT __fastcall Speech_Save(IStream *stream) // RA2: 0x00716790; the markers of the speech queue; no speech is saved (SxoV, ExoV)
{
	int marker = 0x566F7853; // RA2: as above
	HRESULT result = stream->Write(&marker, sizeof(marker), 0); // RA2: as above
	if (SUCCEEDED(result)) { // RA2: as above
		marker = 0x566F7845; // RA2: as above
		result = stream->Write(&marker, sizeof(marker), 0); // RA2: as above
	}
	return result; // RA2: as above
}
