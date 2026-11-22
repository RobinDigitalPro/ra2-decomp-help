// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006CA680 (17 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2914e0 (VA 0x006914E0, 32 bytes incl. padding)
// RA2 symbol : ?Parse_Duration@@YIXPAGPAVSubTitle@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5161)
// source TU  : src/m85/src/subtitle2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: Duration=: how long the subtitle stays; a zero keeps the 20 seconds.
/// </summary>
void __fastcall Parse_Duration(wchar_t * value, SubTitle * subtitle) // RA2: 0x0069BE40
{
	unsigned long duration = Parse_Timecode(value); // RA2: as above
	if (duration > 0) { // RA2: as above
		subtitle->Set_Display_Duration(duration); // RA2: as above
	}
}
