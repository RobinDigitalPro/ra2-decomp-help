// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00780A00 (132 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x3339b0 (VA 0x007339B0, 144 bytes incl. padding)
// RA2 symbol : ?Get_Locale_Name@@YI?AVWideWstring@@H@Z
// similarity : 0.9762 (very-similar, masked instruction tokens; shape 0.8750)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

WideWstring Get_Locale_Name(int locale) // RA2: 0x0073F1C0, the localized name of a locale number, from the string "WOL:Locale" and the number in two digits
{
	Wstring label = "WOL:Locale" + Wstring_FromInt(locale, 2); // RA2: as above
	WideWstring text(StringTable::LoadString(label.get(), NULL, "C:\\RA2\\wonline.cpp", 2345)); // RA2: as above // level-2 1.001: line literal
	if (locale < 37) { // RA2: both ways return the same text, the test is kept
		return(text);
	} else {
		return(text);
	}
}
