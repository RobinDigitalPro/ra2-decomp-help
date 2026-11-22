// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005BC530 (426 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x19a920 (VA 0x0059A920, 432 bytes incl. padding)
// RA2 symbol : ?Create_Debug_Window@@YIXXZ
// similarity : 0.9853 (very-similar, masked instruction tokens; shape 0.9784)
// source TU  : src/m85/src/motlib.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void Create_Debug_Window(void) // level-2 1.001: 0x19A920, adopted from gibbo101 (FUN_005BC530)
{
	DebugWindow = CreateDialogParamA(DebugInstance, MAKEINTRESOURCE(248), DebugParentWindow, (DLGPROC)Debug_Window_Proc, 0);
	Set_Debug_Window_Style(DebugWindow);
	HDC dc = GetDC(DebugWindow);

	LOGFONT lf;
	lf.lfHeight = -MulDiv(8, GetDeviceCaps(dc, LOGPIXELSY), 72);
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = 0;
	lf.lfItalic = 0;
	lf.lfUnderline = 0;
	lf.lfStrikeOut = 0;
	lf.lfCharSet = 0;
	lf.lfOutPrecision = 0;
	lf.lfClipPrecision = 0;
	lf.lfQuality = 0;
	lf.lfPitchAndFamily = 0;
	strcpy(lf.lfFaceName, "Courier");
	DebugFont = CreateFontIndirect(&lf);
	HGDIOBJ old = SelectObject(dc, DebugFont);
	GetTextMetrics(dc, &DebugTextMetric);
	SelectObject(dc, old);
	DebugBackColor = GetSysColor(COLOR_BTNFACE);
	DebugTextColor = GetSysColor(COLOR_WINDOWTEXT);

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = DebugTextMetric.tmMaxCharWidth * 79 + 20;
	rect.bottom = (DebugTextMetric.tmExternalLeading + DebugTextMetric.tmHeight) * 25 + 20; // level-2 1.001: operand order fixes the field load order (tmHeight first, as 0x59aa23)
	AdjustWindowRect(&rect, WS_CAPTION, FALSE);
	RECT parent;
	GetWindowRect(DebugParentWindow, &parent);
	MoveWindow(DebugWindow, parent.right + 5, 0, rect.right - rect.left, rect.bottom - rect.top, TRUE);
	ShowWindow(DebugWindow, SW_HIDE);
	SetFocus(DebugParentWindow);
	ReleaseDC(DebugWindow, dc);
}
