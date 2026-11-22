// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004129B0 (8 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x12710 (VA 0x00412710, 16 bytes incl. padding)
// RA2 symbol : ?Tracker_Debug_String@@YIXPBD@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5000)
// source TU  : src/m85/src/atracker.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Passes a text to the debug output; nothing calls it.
/// </summary>
void __fastcall Tracker_Debug_String(char const * text) // RA2: 0x00412710
{
	DebugString(text);
}
