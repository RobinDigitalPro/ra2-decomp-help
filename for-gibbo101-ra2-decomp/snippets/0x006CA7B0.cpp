// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006CA7B0 (9 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x291610 (VA 0x00691610, 16 bytes incl. padding)
// RA2 symbol : ?Parse_Text@@YIXPAGPAVSubTitle@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5333)
// source TU  : src/m85/src/subtitle2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: Text=: the caption.
/// </summary>
void __fastcall Parse_Text(wchar_t * value, SubTitle * subtitle) // RA2: 0x0069BF70
{
	subtitle->Set_Caption(value); // RA2: as above
}
