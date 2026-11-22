// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00786390 (300 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x336950 (VA 0x00736950, 304 bytes incl. padding)
// RA2 symbol : ?Init_Wonline@@YIHXZ
// similarity : 0.9773 (very-similar, masked instruction tokens; shape 0.9778)
// source TU  : src/m85/src/wonline.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int Init_Wonline(void) // RA2: 0x00742390, not in TibSun: brings the chat services up once (the work Login_WOL did itself in TibSun), 1 when they already are, else the result of Startup_Chat
{
	if (g_WOLInitialized) return(1); // RA2: as above
	g_WOLInitialized = true; // RA2: set before the services come up
	Init_Lobby_Entries(); // RA2: the fixed lobby entries (open, closed, computers)
	Clear_Slot_Lists(); // RA2: as above
	Reset_Slots(); // RA2: as above

	DWORD value = 0;
	HKEY rKey;
	char regkey[256];
	if (APP_REG_KEY != NULL && strlen(APP_REG_KEY)) {
		strcpy(regkey, APP_REG_KEY);
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, regkey, 0, KEY_READ, &rKey) == ERROR_SUCCESS) {
			DWORD type;
			DWORD valuesize = sizeof(value);
			RegQueryValueEx(rKey, "SKU", NULL, &type, (LPBYTE)&value, &valuesize);
			RegCloseKey(rKey);
		}
	}

	value &= 0xFF; // RA2: as above
	g_LanguageCode = value; // RA2: as above
	g_GameSKU = value + 0x2100; // RA2: the SKU of Red Alert 2 plus the language

	Reset_WOL_Globals();
	g_IgnoreNetStatus = true;
	for (int i = 0; i < EV_COUNT; i++) {
		g_WaitEventHandles[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
	}
	return(Startup_Chat(ProgramInstance)); // RA2: 1 on success, -2 when a service is missing
}
