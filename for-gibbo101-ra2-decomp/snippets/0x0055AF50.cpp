// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0055AF50 (7 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x13ba10 (VA 0x0053BA10, 16 bytes incl. padding)
// RA2 symbol : ?Set_Buffer_Zone_Width@@YIXH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.3077)
// source TU  : src/m85/src/logic.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2
/// </summary>
void __fastcall Set_Buffer_Zone_Width(int value) // RA2: at 0x53D830 (name chosen here)
{
	Detail::BufferZoneWidth = value;
}
