// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00709460 (32 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2c9860 (VA 0x006C9860, 32 bytes incl. padding)
// RA2 symbol : ?Is_Not_AnimType_Building_Bullet@@YGHW4RTTIType@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/techno.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Whether objects of this kind are not animation types, buildings or bullets.
/// </summary>
int __stdcall Is_Not_AnimType_Building_Bullet(RTTIType rtti) // RA2: not in TibSun, at 0x6D42F0
{
	if (rtti != RTTI_ANIMTYPE && rtti != RTTI_BUILDING && rtti != RTTI_BULLET) {
		return(1);
	}
	return(0);
}
