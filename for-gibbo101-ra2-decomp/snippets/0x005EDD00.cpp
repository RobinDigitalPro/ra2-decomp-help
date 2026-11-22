// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005EDD00 (218 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c5850 (VA 0x005C5850, 224 bytes incl. padding)
// RA2 symbol : ?Limit_Name_Text@@YI?AVWideWstring@@PAUHWND__@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9589)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

WideWstring __fastcall Limit_Name_Text(HWND control) // RA2: 0x005CCF50, not in TibSun; the text of a name edit with the line breaks cut off; it is cut to what the lobby allows: 120 characters, or the ones below 0x100 after the first wider character (40 at least) in a name with wider characters
{
	WideWstring text; // RA2: as above
	Get_Window_Wide_Text(control, text); // RA2: as above
	unsigned int limit = 120; // RA2: as above
	if (!text.Is_Narrow()) { // RA2: as above
		unsigned int i; // RA2: as above
		for (i = 0; i < text.length(); i++) { // RA2: as above
			if (text.getChar(i) > 256) { // RA2: as above
				break; // RA2: as above
			}
		}
		limit = i - 1; // RA2: as above
		if (limit <= 40) { // RA2: as above
			limit = 40; // RA2: as above
		}
	}
	if (text.length() > limit) { // RA2: as above
		text.truncate(limit); // RA2: as above
		SendMessageA(control, 0x4B2, 0, (LPARAM)text.text()); // RA2: as above
	}
	{
		WideWstring line_breaks(L"\n\r"); // RA2: as above
		text.trimTrailing(line_breaks); // RA2: as above
	}
	return(text); // RA2: as above
}
