// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0053EC40 (40 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1228e0 (VA 0x005228E0, 48 bytes incl. padding)
// RA2 symbol : ?Set_Key_State@@YIXI_N@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.7143)
// source TU  : src/m85/src/audfile.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// While recording or playing back, stores the state of a key.
/// </summary>
void Set_Key_State(unsigned key, bool release) // RA2: 0x005233A0
{
	if (AudioFileMode != 0) { // RA2: as above
		KeyStates[key & 0xFF] = release ? 0 : 0x8000; // RA2: as above
	}
}
