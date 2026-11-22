// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00752460 (32 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x30a460 (VA 0x0070A460, 32 bytes incl. padding)
// RA2 symbol : ?Name_From@VoxClass@@SIPBDH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/vox.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

char const *__fastcall VoxClass::Name_From(int index) // RA2: 0x007158A0; the name of the VoxClass at an index, "none" out of range
{
	if (index != -1 && index >= 0 && index < Voxs.Count()) { // RA2: as above
		return Voxs[index]->Name; // RA2: as above
	}
	return "none"; // RA2: as above
}
