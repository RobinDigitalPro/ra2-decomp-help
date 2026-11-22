// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00733160 (74 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2ec7b0 (VA 0x006EC7B0, 80 bytes incl. padding)
// RA2 symbol : ?Detach_From_Command_List@@YIXPAVAbstractClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9189)
// source TU  : src/m85/src/uicmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Takes an object that is going away out of the list a type, state or rank selection works on.
/// </summary>
void __fastcall Detach_From_Command_List(AbstractClass * object) // RA2: 0x006F7970
{
	if (TypeSelectList != NULL) { // RA2: the list is searched from its end and the first hit is removed with Delete_Index
		for (int index = TypeSelectList->Count() - 1; index >= 0; index--) { // RA2: the executable searches from the end
			if ((*TypeSelectList)[index] == object) { // RA2: as above
				TypeSelectList->Delete_Index(index); // RA2: as above
				return; // RA2: as above
			}
		}
	}
}
