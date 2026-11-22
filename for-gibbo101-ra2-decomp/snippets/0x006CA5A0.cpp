// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006CA5A0 (196 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x291400 (VA 0x00691400, 208 bytes incl. padding)
// RA2 symbol : ?Parse_Timecode@@YIKPBG@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9241)
// source TU  : src/m85/src/subtitle2.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: a time as hours:minutes:seconds:hundredths in ticks of 1/60 second.
/// </summary>
unsigned long __fastcall Parse_Timecode(wchar_t const * text) // RA2: 0x0069BD60
{
	wchar_t buf[12]; // RA2: as above
	wchar_t * colon; // RA2: as above

	wcsncpy(buf, text, 12); // RA2: as above
	buf[11] = 0; // RA2: as above

	colon = wcschr(buf, L':'); // RA2: as above
	*colon = 0; // RA2: as above
	unsigned long hours = wcstoul(buf, NULL, 10); // RA2: as above

	wchar_t * minutes = colon + 1; // RA2: as above
	colon = wcschr(minutes, L':'); // RA2: as above
	*colon = 0; // RA2: as above
	unsigned long mins = wcstoul(minutes, NULL, 10); // RA2: as above

	wchar_t * seconds = colon + 1; // RA2: as above
	colon = wcschr(seconds, L':'); // RA2: as above
	*colon = 0; // RA2: as above
	unsigned long secs = wcstoul(seconds, NULL, 10); // RA2: as above

	wchar_t * frames = colon + 1; // RA2: as above
	unsigned long hundredths = wcstoul(frames, NULL, 10); // RA2: as above

	return (((hours * 60 + mins) * 60 + secs) * 60) + (hundredths * 60) / 100; // RA2: as above
}
