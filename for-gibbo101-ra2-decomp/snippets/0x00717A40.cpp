// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00717A40 (3 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1d6fc0 (VA 0x005D6FC0, 16 bytes incl. padding)
// RA2 symbol : ?Hash_Key@@YIIAAI@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.2353)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Fetches the hash value for a window handle.
/// This is the hash routine handed to the dictionaries that key their entries by the
/// window handle of a subclassed control.
/// </summary>
/// <returns>Returns with the handle itself, taken as an unsigned value.</returns>
unsigned int __fastcall Hash_Key(unsigned int &key) // RA2: the key as its own hash
{
    return key; // RA2: as above
}
