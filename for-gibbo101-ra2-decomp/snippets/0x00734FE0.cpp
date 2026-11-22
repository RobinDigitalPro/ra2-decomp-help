// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00734FE0 (115 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2eece0 (VA 0x006EECE0, 128 bytes incl. padding)
// RA2 symbol : ?Message_Box_Wide@@YIHPAUHWND__@@PBG1I@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8571)
// source TU  : src/m85/src/strtable.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// A message box for wide text: the text and caption are narrowed (at most 5120 and 2048 bytes) for MessageBoxA.
/// </summary>
int __fastcall Message_Box_Wide(HWND window, wchar_t const * text, wchar_t const * caption, unsigned int type) // RA2: 0x006FA040
{
	char narrow_text[0x1400]; // RA2: as above
	char narrow_caption[0x800]; // RA2: as above
	WideCharToMultiByte(0, 0, text, -1, narrow_text, sizeof(narrow_text), 0, 0); // RA2: the ANSI code page
	WideCharToMultiByte(0, 0, caption, -1, narrow_caption, sizeof(narrow_caption), 0, 0); // RA2: as above
	return MessageBoxA(window, narrow_text, narrow_caption, type); // RA2: as above
}
