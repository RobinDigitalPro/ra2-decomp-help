// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00753000 (416 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x30afb0 (VA 0x0070AFB0, 416 bytes incl. padding)
// RA2 symbol : ?Process@VoxClass@@SIXAAVCCINIClass@@@Z
// similarity : 0.9545 (very-similar, masked instruction tokens; shape 0.9665)
// source TU  : src/m85/src/vox.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall VoxClass::Process(CCINIClass &ini) // RA2: 0x007163F0; makes (or finds) a VoxClass for each [DialogList] entry of EVA.ini, which then reads its own section
{
	if (ini.Is_Present("DialogList")) { // RA2: as above
		int count = ini.Entry_Count("DialogList"); // RA2: as above
		for (int index = 0; index < count; index++) { // RA2: as above
			char name[200]; // RA2: as above
			if (ini.Get_String("DialogList", ini.Get_Entry("DialogList", index), "", name, sizeof(name))) { // RA2: as above
				VoxClass *vox; // RA2: as above
				int vox_index = Vox_From_Name(name); // RA2: as above
				if (vox_index == -1) { // RA2: as above
					vox = new VoxClass(name); // RA2: as above
				} else {
					vox = Voxs[vox_index]; // RA2: as above
				}
				vox->Read_INI(ini); // RA2: as above
			}
		}
	}
}
