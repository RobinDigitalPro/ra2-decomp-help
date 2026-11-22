// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00753250 (67 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x30b200 (VA 0x0070B200, 80 bytes incl. padding)
// RA2 symbol : ?Vox_From_Name@@YI?AW4VoxType@@PBD@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8312)
// source TU  : src/m85/src/vox.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

VoxType __fastcall Vox_From_Name(char const * name) // RA2: 0x00716640; the index of the VoxClass of a name, -1 for none or a null name
{
	if (name == NULL) { // RA2: as above
		return (VoxType)-1; // RA2: as above
	}
	return (VoxType)Index_Of_Name(name); // RA2: as above
}
