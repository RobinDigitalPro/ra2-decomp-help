// ra2-decomp help snippet, update 2 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006BB9A0 (10261 bytes; gibbo101/ra2-decomp name: System::WinMain)
// RA2 address: RVA 0x283970 (VA 0x00683970, 10070 bytes without padding)
// RA2 symbol : _WinMain@16
// similarity : 0.8474 (partial, masked instruction tokens; shape 0.9584)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/startup.cpp
// License    : GPL-3.0-or-later. Our source is GPL and contains EA GPL code (section 7 terms)
//              and code adapted from mischa85/RedAlert2 and gibbo101/ra2-decomp; their
//              credits are kept. The notice of the source file follows. See ../README.md.
// Use        : a read-only lead. RA2 layouts and names; port it and match it on your own checker.

/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2025 Electronic Arts Inc.
 * Copyright 2026 OpenTS contributors
 *
 * Contains material derived from Electronic Arts source code.
 * Modified by OpenTS contributors, 2026.
 * EA's GPLv3 Section 7 additional terms and supplemental warranty
 * disclaimers apply; see LICENSE.md.
 ******************************************************************************/

/***********************************************************************************************
 * main -- Initial startup routine (preps library systems).                                    *
 *                                                                                             *
 *    This is the routine that is first called when the program starts up. It basically        *
 *    handles the command line parsing and setting up library systems.                         *
 *                                                                                             *
 * INPUT:   argc  -- Number of command line arguments.                                         *
 *                                                                                             *
 *          argv  -- Pointer to array of command line argument strings.                        *
 *                                                                                             *
 * OUTPUT:  Returns with execution failure code (if any).                                      *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   03/20/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
int CALLBACK WinMain ( HINSTANCE instance , HINSTANCE , char * command_line , int command_show )
{
	int		argc;       //Command line argument count
	char *	argv[20];   //Pointers to command line arguments
	char	path_to_exe[132];
	wchar_t	buffer[512]; // level-2 1.001: the message texts are wide (string table)

#ifdef STEVES_NEW_CATCHER
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
#endif

	ProgramInstance = instance;

	MainThread = (HANDLE)GetCurrentThreadId();

	/*
	** level-2 1.001: the 1.001 size report has 56 entries (lines 1560..1615). The sizes are
	** the 1.001 class sizes, which the 1.006 headers do not reproduce, so they are given as
	** values; the class in each comment is the 1.006 list entry at the same position.
	*/
#line 1560
	DebugString("%d-%d\n", __LINE__, 0x98);		// CrateData
	DebugString("%d-%d\n", __LINE__, 0x4C);		// CrateShares
	DebugString("%d-%d\n", __LINE__, 0x4C);		// CrateAnims
	DebugString("%d-%d\n", __LINE__, 0x13);		// level-2 1.001: an entry the 1.006 list lacks (unidentified)
	DebugString("%d-%d\n", __LINE__, 0xE18);	// Tactical
	DebugString("%d-%d\n", __LINE__, 0x5C0);	// AircraftClass
	DebugString("%d-%d\n", __LINE__, 0xBA8);	// AircraftTypeClass
	DebugString("%d-%d\n", __LINE__, 0x110);	// AITriggerTypeClass
	DebugString("%d-%d\n", __LINE__, 0x1A8);	// AnimClass
	DebugString("%d-%d\n", __LINE__, 0x330);	// AnimTypeClass
	DebugString("%d-%d\n", __LINE__, 0x78);		// BaseClass
	DebugString("%d-%d\n", __LINE__, 0x5E0);	// BuildingClass
	DebugString("%d-%d\n", __LINE__, 0x1418);	// BuildingTypeClass
	DebugString("%d-%d\n", __LINE__, 0x148);	// BulletClass
	DebugString("%d-%d\n", __LINE__, 0x2C8);	// BulletTypeClass
	DebugString("%d-%d\n", __LINE__, 0x148);	// CellClass
	DebugString("%d-%d\n", __LINE__, 0x70);		// FactoryClass
	DebugString("%d-%d\n", __LINE__, 0x15F90);	// HouseClass
	DebugString("%d-%d\n", __LINE__, 0x1B0);	// HouseTypeClass
	DebugString("%d-%d\n", __LINE__, 0x5D8);	// InfantryClass
	DebugString("%d-%d\n", __LINE__, 0xC18);	// InfantryTypeClass
	DebugString("%d-%d\n", __LINE__, 0x18);		// LayerClass
	DebugString("%d-%d\n", __LINE__, 0x4F3C);	// MouseClass
	DebugString("%d-%d\n", __LINE__, 0xE18);	// MapEditTactical
	DebugString("%d-%d\n", __LINE__, 0x9C);		// OverlayClass
	DebugString("%d-%d\n", __LINE__, 0x288);	// OverlayTypeClass
	DebugString("%d-%d\n", __LINE__, 0x9C);		// SmudgeClass
	DebugString("%d-%d\n", __LINE__, 0x274);	// SmudgeTypeClass
	DebugString("%d-%d\n", __LINE__, 0xD4);		// TaskForceClass
	DebugString("%d-%d\n", __LINE__, 0x9C);		// TeamClass
	DebugString("%d-%d\n", __LINE__, 0xF0);		// TeamTypeClass
	DebugString("%d-%d\n", __LINE__, 0xC8);		// TerrainClass
	DebugString("%d-%d\n", __LINE__, 0x28C);	// TerrainTypeClass
	DebugString("%d-%d\n", __LINE__, 0x44);		// TriggerClass
	DebugString("%d-%d\n", __LINE__, 0xB4);		// TriggerTypeClass
	DebugString("%d-%d\n", __LINE__, 0xA4);		// TagTypeClass
	DebugString("%d-%d\n", __LINE__, 0x38);		// TagClass
	DebugString("%d-%d\n", __LINE__, 0x7D0);	// UnitClass
	DebugString("%d-%d\n", __LINE__, 0xC10);	// UnitTypeClass
	DebugString("%d-%d\n", __LINE__, 0x2460);	// ScenarioClass
	DebugString("%d-%d\n", __LINE__, 0xEC);		// SuperWeaponTypeClass
	DebugString("%d-%d\n", __LINE__, 0x68);		// SuperClass
	DebugString("%d-%d\n", __LINE__, 0x1B0);	// Ground
	DebugString("%d-%d\n", __LINE__, 0x14C0);	// RulesClass
	DebugString("%d-%d\n", __LINE__, 0x3C0);	// MissionControl
	DebugString("%d-%d\n", __LINE__, 1);
	DebugString("%d-%d\n", __LINE__, 0x418);	// TechnoClass
	DebugString("%d-%d\n", __LINE__, 0xD8);		// RadioClass
	DebugString("%d-%d\n", __LINE__, 0xBC);		// MissionClass
	DebugString("%d-%d\n", __LINE__, 8);
	DebugString("%d-%d\n", __LINE__, 0x18);		// StageClass
	DebugString("%d-%d\n", __LINE__, 8);
	DebugString("%d-%d\n", __LINE__, 8);
	DebugString("%d-%d\n", __LINE__, 0x10);		// StorageClass
	DebugString("%d-%d\n", __LINE__, 0x20);		// DelayTimerClass
	DebugString("%d-%d\n", __LINE__, 0x18);		// FacingClass

	/*
	** level-2 1.001: the game only runs when it was started by the launcher.
	*/
	if (!CopyProtection::IsLauncherRunning()) {
		DebugString("Launcher not running....Bail!\n");
		return(EXIT_SUCCESS);
	}

	/*
	 * Create a mutex with a unique name to TibSun in order to determine if
	 * our app is already running.
	 *
	 * WARNING: DO NOT use this number for any other application except TibSun
	 */
	AppMutex = ::CreateMutex (NULL, FALSE, APP_GUID);

	//
	// Is there already an instance of this app somewhere?
	//
	if (::GetLastError () == ERROR_ALREADY_EXISTS) {
		//
		// Find the previous instance
		//
		HWND main_wnd = ::FindWindow (APP_GUID, NULL);
		if (main_wnd != NULL) {
			::SetForegroundWindow (main_wnd);
			::ShowWindow (main_wnd, SW_RESTORE);
		}
		if (AppMutex != NULL) {
			CloseHandle(AppMutex);
			AppMutex = NULL;
		}
		DebugString("TibSun is already running...Bail!\n");
		return(EXIT_SUCCESS);
	} else {

		DebugString("Create AppMutex okay.\n");

		//
		// Obtain the mutex unique to the Renegade AutoPlay application.
		//
		// WARNING: DO NOT use this number for any other application except Renegade AutoPlay
		//
		do
		{
			//
			// Attempt to open the mutex
			//
			AutoPlayMutex = ::OpenMutex (MUTEX_ALL_ACCESS, FALSE, AUTOPLAY_GUID);
			if (AutoPlayMutex != NULL) {
				DebugString( "Waiting for Autoplay to quit!\n");
				if (::WaitForSingleObject (AutoPlayMutex, 30000) == WAIT_FAILED) {
					DebugString ("Failed waiting for AutoPlayMutex\n");
					::CloseHandle (AutoPlayMutex);
					AutoPlayMutex = NULL;
				}
			}

			/*
			 * Create a mutex with a name unique to the TibSun AutoPlay application.
			 * This prevents the autoplay from running since it cannot get the mutex.
			 * TibSun needs both of these mutexs before it is allowed to run.
			 */
			if (AutoPlayMutex == NULL) {
				AutoPlayMutex = CreateMutex (NULL, FALSE, AUTOPLAY_GUID);
				if (GetLastError () == ERROR_ALREADY_EXISTS) {
					CloseHandle (AutoPlayMutex);
					AutoPlayMutex = NULL;
					Sleep (2500);
				} else {
					DebugString("Create AutoPlayMutex.\n");
				}
			}
		} while (AutoPlayMutex == NULL);

		DebugString ("Got AutoPlayMutex okay.\n");
	}

	_controlfp(_RC_CHOP, MCW_RC);
	set_control_word();

	/*
	**	Get the full path to the .EXE
	*/
	GetModuleFileName (instance, &path_to_exe[0], sizeof(path_to_exe));

	/*
	**	First argument is supposed to be a pointer to the .EXE that is running
	**
	*/
	argc=1;                     //Set argument count to 1
	argv[0]=&path_to_exe[0];    //Set 1st command line argument to point to full path

	/*
	**	Get pointers to command line arguments just like if we were in DOS
	**
	*/
	char *token = strtok(command_line, " ");
	while (argc < ARRAY_SIZE(argv) && token != NULL) {
		argv[argc++] = strtrim(token);
		token = strtok(NULL, " ");
	}

	/*
	**	Change directory to the where the executable is located. Handle the
	**	case where there is no path attached to argv[0].
	*/
	char drive[_MAX_DRIVE];
	char path[_MAX_PATH];
	char dir[_MAX_DIR];
	_splitpath(argv[0], drive, dir, NULL, NULL);
	_makepath(path, drive, dir, NULL, NULL);
	SetCurrentDirectory(path);

	int retval = EXIT_FAILURE; // level-2 1.001: local names decide SEH frame slots; retval and fileptr give the 1.001 slots (were error_code, cfile)

	if (Parse_Command_Line(argc, argv)) {

		RawFileClass *fileptr = new RawFileClass(CONFIG_FILE_NAME);

		/*
		** Set the options as requested by the setup program
		*/
		Read_Setup_Options(fileptr); // level-2 1.001: INFERRED single-caller helper (RA1 STARTUP.CPP form), expanded inline here

		Keyboard = new KeyboardClass();

		/*
		**	If there is not enough disk space free, don't allow the product to run.
		*/
		if (Disk_Space_Available() < INIT_FREE_DISK_SPACE) {
			swprintf(buffer, StringTable::LoadString("TXT_CRITICALLY_LOW", NULL, "C:\\RA2\\Startup.CPP", 1830), (INIT_FREE_DISK_SPACE) / (1024 * 1024)); // level-2 1.001: wide text, line 1830
			int reply = Message_Box_Wide(NULL, buffer, StringTable::LoadString("TXT_SHORT_TITLE", NULL, "C:\\RA2\\Startup.CPP", 1831), MB_ICONQUESTION|MB_YESNO); // level-2 1.001: as above, line 1831
			if (reply == IDNO) {
				OleUninitialize();
				return(EXIT_FAILURE);
			}
		}

		OleInitialize(NULL); // level-2 1.001: COM is prepared after the configuration is read

		if (RegisterClasses()) {
			exit(EXIT_FAILURE);
		}

		DebugString("Init Encryption Keys.\n"); // level-2 1.001: the keys are prepared here
		Init_Keys();

		/*
		** level-2 1.001: LANGUAGE.MIX is opened from the local disk before the string table is read.
		*/
		DiskID cd = CD::Get_Required_Disk();
		CD::Set_Required_Disk(DISK_LOCAL);
		Mix_81F7FC = new MFCD("LANGUAGE.MIX", &FastKey);
		CD::Set_Required_Disk(cd);

		atexit(Prog_End);

		Start_Mouse_Thread(); // level-2 1.001: as above

		if (!StringTable::LoadFile("ra2.str")) { // level-2 1.001: as above
			MessageBox(NULL, "Unable to initialize 'ra2.csf', please reinstall Red Alert.\nKeine Initialisierung von 'ra2.csf' m\xf6glich. Bitte installieren Sie Red Alert erneut.\nInitialisation de 'ra2.csf' impossible. Veuillez r\xe9installer Red Alert.", "Red Alert 2", MB_ICONERROR);
			return(EXIT_SUCCESS);
		}

		if (!Init_Language_Resources(true)) {
			return(EXIT_SUCCESS);
		}

		if (!GetSystemMetrics(SM_MOUSEPRESENT) || !GetSystemMetrics(SM_CMOUSEBUTTONS)) {
			Message_Box_Wide(NULL, StringTable::LoadString("TXT_MOUSE_REQUIRED", NULL, "C:\\RA2\\Startup.CPP", 1894), StringTable::LoadString("TXT_SHORT_TITLE", NULL, "C:\\RA2\\Startup.CPP", 1894), MB_ICONERROR); // level-2 1.001: line 1894
			exit(EXIT_FAILURE);
		}

		if (GetDllVersion("comctl32.dll") < PACKVERSION(4, 70)) {
			swprintf(buffer, StringTable::LoadString("TXT_DLL_INVALID", NULL, "C:\\RA2\\Startup.CPP", 1904), "comctl32.dll", 4, 70, "comctl32.dll"); // level-2 1.001: line 1904
			Message_Box_Wide(NULL, buffer, StringTable::LoadString("TXT_SHORT_TITLE", NULL, "C:\\RA2\\Startup.CPP", 1905), MB_ICONERROR); // level-2 1.001: line 1905
			exit(EXIT_FAILURE);
		}

		RegisterActiveObject((IUnknown *)&Map, CLSID_TiberianSun, ACTIVEOBJECT_WEAK, &dwRegisterMap);

		if (Options.ScreenWidth == -1 || Options.ScreenHeight == -1) {
			Options.ScreenWidth = 640;

			if (WinVersion.Is_WinNTx() || GetVideoMemory() > 0x200000) {
				Options.ScreenHeight = 480;
			} else {
				Options.ScreenHeight = 400;
			}
		}

		BOOL video_success = FALSE;

		if (Debug_IngameModeChange) {
			Create_Main_Window(instance, command_show, 640, 400);
			Prep_Direct_Draw(); // level-2 1.001: the audio is not started here
			if (WindowedMode) {
				VisibleRect = Rect(0,0,640,400);
				VideoModeWidth = VisibleRect.Width;
				VideoModeHeight = VisibleRect.Height;
				VideoModeBitsPerPixel = HicolorFlag ? 16 : 8;
			} else {
				/*
				** Set 640x400 video mode. If its not available then try for 640x480
				*/
				VisibleRect = Rect(0,0,640,400);
				video_success = Set_Video_Mode(MainWindow, 640, 400, HicolorFlag ? 16 : 8);
				if (!video_success) {
					video_success = Set_Video_Mode(MainWindow, 640, 480, HicolorFlag ? 16 : 8);
					VisibleRect = Rect(0,0,640,480);
					if (!video_success) {
						Destroy_Direct_Draw();
						Message_Box_Wide(MainWindow, StringTable::LoadString("TXT_VIDEO_ERROR", NULL, "C:\\RA2\\Startup.CPP", 2048), StringTable::LoadString("TXT_SHORT_TITLE", NULL, "C:\\RA2\\Startup.CPP", 2049), MB_ICONWARNING); // level-2 1.001: lines 2048/2049
						exit(EXIT_FAILURE);
					}
				}
			}
		} else {
			Create_Main_Window(instance, command_show, Options.ScreenWidth, Options.ScreenHeight);
			Prep_Direct_Draw();
			if (WindowedMode) {
				VisibleRect = Rect(0,0,Options.ScreenWidth,Options.ScreenHeight);
				VideoModeWidth = Options.ScreenWidth;
				VideoModeHeight = Options.ScreenHeight;
				VideoModeBitsPerPixel = HicolorFlag ? 16 : 8;
			} else {
				/*
				 * Set desired video mode. If its not available then try for 640x480
				 */
				video_success = Set_Video_Mode(MainWindow, Options.ScreenWidth, Options.ScreenHeight, HicolorFlag ? 16 : 8);
				VisibleRect = Rect(0,0,Options.ScreenWidth,Options.ScreenHeight);
				if (!video_success) {
					if (Options.ScreenWidth != 640 || Options.ScreenHeight != 480) {
						Options.ScreenWidth = 640;
						Options.ScreenHeight = 480;
						video_success = Set_Video_Mode(MainWindow, Options.ScreenWidth, Options.ScreenHeight, HicolorFlag ? 16 : 8);
						VisibleRect = Rect(0,0,Options.ScreenWidth,Options.ScreenHeight);
					}
					if (!video_success) {
						Destroy_Direct_Draw();
						Message_Box_Wide(MainWindow, StringTable::LoadString("TXT_VIDEO_ERROR", NULL, "C:\\RA2\\Startup.CPP", 2087), StringTable::LoadString("TXT_SHORT_TITLE", NULL, "C:\\RA2\\Startup.CPP", 2088), MB_ICONWARNING); // level-2 1.001: lines 2087/2088
						exit(EXIT_FAILURE);
					}
				}
			}
		}

		/*
		** level-2 1.001: -record and -play open the session recording here.
		*/
		if (RecordPlayRequest && Audio_File_Init(1000, 0x19000)) {
			if (RecordPlayRequest == 1) {
				Audio_File_Create_Stream("session.ipb");
			} else if (RecordPlayRequest == 2) {
				Audio_File_Open_Stream("session.ipb");
			}
		}

		VisibleSurface = DSurface::Create_Primary();

		int visible_bpp = VisibleSurface->Bytes_Per_Pixel();
		HicolorFlag = visible_bpp == 2;
		if (!HicolorFlag) {
			Message_Box_Wide(MainWindow, StringTable::LoadString("TXT_INVALIDMODE", NULL, "C:\\RA2\\Startup.CPP", 2117), StringTable::LoadString("TXT_SHORT_TITLE", NULL, "C:\\RA2\\Startup.CPP", 2117), MB_ICONEXCLAMATION); // level-2 1.001: line 2117
			Emergency_Exit();
		}

		if (!CopyProtection::NotifyLauncher()) { // level-2 1.001: as above
			DebugString("Failed to notify launcher\n");
			exit(EXIT_FAILURE);
		}

		do {
			Windows_Message_Handler();
		}
		while (!GameInFocus);

		SurfacesRestored = false;

		if (!WindowedMode) {
			VisibleSurface->Fill(0);
		}

		Func_59A570(ProgramInstance, MainWindow, WindowedMode); // level-2 1.001: as above
		Planning_Reset(); // level-2 1.001: as above

		/*
		** level-2 1.001: INFERRED form. The composite, tile and sidebar rectangles are temporaries
		** of this call (the sidebar width is a variable). In 1.001's SEH frame they sit among the
		** temporaries, below every named local, in the order sidebar, tile, composite; named Rect
		** locals sort by name among the named locals instead. gibbo101's YR 1.001 WinMain notes
		** report the same form ("Rect temporaries straight into Allocate_Surfaces").
		*/
		Allocate_Surfaces(VisibleRect, Rect(0,0,VisibleRect.Width-SidebarWidth, VisibleRect.Height), Rect(0,0,VisibleRect.Width-SidebarWidth, VisibleRect.Height), Rect(0,0,SidebarWidth,VisibleRect.Height), false);
		if (UseDirect3D) { // level-2 1.001: as above
			Init_Direct3D();
		}
		LogicalSurface = HiddenSurface;
		Update_Visible_Surface(true, HiddenSurface);

		/*
		** level-2 1.001: INFERRED named alias for the new depth buffer. It is the one 4-byte named
		** local of this block that 1.001's frame has beyond ours, and calling Set_Scroll through a
		** local drops the inline expansion's `this` slot at the bottom of the frame, which 1.001
		** also lacks (frame 0xe0c). The code is identical to `DepthBuffer->Set_Scroll(...)`.
		** gibbo101's YR 1.001 WinMain needed a zbuf alias local here as well.
		*/
		ZBuffer * zbufptr = DepthBuffer = new ZBuffer(Rect(TacticalRect.X, TacticalRect.Y, 480, 480 - TacticalRect.Y));
		zbufptr->Set_Scroll(ZBUFFER_MAX);

		AlphaBuffer = new ABuffer(Rect(TacticalRect.X, TacticalRect.Y, 480, 480 - TacticalRect.Y));

		MouseCursor = new WWMouseClass(VisibleSurface, MainWindow);
		MouseCursor->Hide_Mouse(); // level-2 1.001: the mouse is hidden here, not captured

		CDFileClass::Set_CD_Drive (CDList.Get_First_CD_Drive());

		/*
		**	Check for forced intro movie run disabling. If the conquer
		**	configuration file says "no", then don't run the intro.
		*/
		DiskID diskid = CD::Get_Current_Disk(60); // RA2: a 60 timeout; level-2 1.001: INFERRED name (was disk), see wolopt
		Get_Performance_Profile(); // level-2 1.001: as above
		if (!Special.IsFromInstall && diskid > DISK_ANY) { // level-2 1.001: one Play key for every disk
			Special.IsFromInstall = ConfigINI.Get_Bool("Intro", "Play", true);
		}

		/*
		** level-2 1.001: the WOLAPI registry options set IsEscapeMovies. INFERRED names: in this SEH
		** function local names decide the frame order (OPEN_PATTERNS, local names). 1.001 has wolopt
		** at -0x720 above video_success at -0x724, and fileptr at -0x70c directly below visible_bpp;
		** the names wolopt, diskid and zbufptr give that layout (disk/wolapi did not).
		*/
		WOLAPIOptions wolopt;
		if (!wolopt.Is_Option_1_Clear() && !wolopt.Is_Option_4_Clear() && !wolopt.Is_Option_2_Clear()) {
			Special.IsEscapeMovies = true;
		}

		/*
		**	Regardless of whether we should run it or not, here we're
		**	gonna change it to say "no" in the future.
		*/
		if (Special.IsFromInstall == true) {
			if (diskid > DISK_ANY) {
				Special.IsFromInstall = ConfigINI.Put_Bool("Intro", "Play", false);
			}
			fileptr->Close();
			fileptr->Open(FileClass::READ);
			ConfigINI.Save(*fileptr, false);
		}

		fileptr->Close();
		delete fileptr;

		if (NoExceptionHandler) {

			Main_Game(argc, argv);

		} else {

#if defined(_MSC_VER) && (_MSC_VER <= 1200)
			/*
			**	The __try/__except construct is part of the WIN32 interface. This is not the same
			**	as C++ exception handling. There is no additional code overhead required
			**	with this interface and the compilers exception handling options should be disabled
			**	to prevent the compiler generating additional stack unwinding code.
			*/
			__try {
#else
			SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER) &Top_Level_Exception_Filter);
#endif

				DebugString("Main_Game\n");

				Main_Game(argc, argv);

#if defined(_MSC_VER) && (_MSC_VER <= 1200)
			} __except(Exception_Handler(GetExceptionCode(), GetExceptionInformation())) {};
#else
			/*
			**	Set the exception filter to use on shutdown.
			*/
			SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER) &Top_Level_Exception_Filter);
#endif

#if defined(_MSC_VER) && (_MSC_VER <= 1200)
			SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER) &Top_Level_Exception_Filter);
#endif

		}

		MouseCursor->Hide_Mouse(); // level-2 1.001: hidden again after the game

		HiddenSurface->Fill(0);
		Update_Visible_Surface(true, HiddenSurface);

		/*
		**	Flag that this is a clean shutdown (not killed with Ctrl-Alt-Del)
		*/
		ReadyToQuit = 1;

		Theme.Free_Themes(); // level-2 1.001: the themes and the audio are released here
		Audio_Shutdown();

		/*
		**	Post a message to our message handler to tell it to clean up.
		*/
		PostMessage(MainWindow, WM_DESTROY, 0, 0);

		/*
		**	Wait until the message handler has dealt with the message
		*/
		do
		{
			Windows_Message_Handler();
		}while (ReadyToQuit == 1);

		retval = EXIT_SUCCESS;
	}

	/*
	** level-2 1.001: the subsystems are shut down here as well as in Prog_End.
	*/
	Free_Game_Modes();
	RadarEventClass::Clear();
	Map.DisposeOfArt();
	Free_Scheme_Library();
	Func_59A6F0();
	ObjectTypeClass::Free_One_Time();
	Func_5E2F00();
	Planning_Reset_Wrapper();
	Free_All_Art();
	Clear_Cycle_List();
	Load_Progress_Shutdown();
	Free_Mouse_Shapes();
	Shutdown_Network_5B76A0();

	if (dwRegisterMap != -1) {
		RevokeActiveObject(dwRegisterMap, NULL);
		dwRegisterMap = -1;
	}

	CoDisconnectObject((LPUNKNOWN)&ApplicationInstance, 0);
	OleUninitialize();

	return(retval);
}

// ---- companion (function Read_Setup_Options, from src/m85/src/startup.cpp): the function above depends on it ----
/***********************************************************************************************
 * Read_Setup_Options -- Read stuff in from the INI file that we need to know sooner           *
 *                                                                                             *
 *    level-2 1.001: INFERRED helper. WinMain is its only caller and VC6 expands it inline.    *
 *    Its form follows RA1's STARTUP.CPP Read_Setup_Options; the evidence is WinMain's SEH     *
 *    frame (netptr/netbuf/socket/found/p, node, net, x, i and the IPXAddressClass temporary   *
 *    sit with RegisterClasses' expanded locals, as an inline expansion's do) and its inline   *
 *    budget (with the socket and DestNet code in this helper, WinMain calls the CStreamClass  *
 *    factory ctor and the INIClass ctor out of line, as 1.001 does).                          *
 *                                                                                             *
 * INPUT:    Ptr to config file class                                                          *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 *=============================================================================================*/
static void Read_Setup_Options(RawFileClass * config_file)
{
	ConfigINI.Load(*config_file, false);
	VideoBackBufferAllowed = ConfigINI.Get_Bool("Video", "VideoBackBuffer", true);
	Debug_IngameModeChange = ConfigINI.Get_Bool("Video", "AllowModeToggle", false);
	Options.ScreenWidth = ConfigINI.Get_Int("Video", "ScreenWidth", Options.ScreenWidth);
	Options.ScreenHeight = ConfigINI.Get_Int("Video", "ScreenHeight", Options.ScreenHeight);

	/*
	** See if an alternative socket number has been specified
	*/
	int socket = ConfigINI.Get_Int("Network", "Socket", 0);
	if (socket > 0) {
		socket += 0x4000;
		if (socket >= 0x4000 && socket < 0x8000) {
			Ipx.Set_Socket(socket);
		}
	}

	/*
	** See if a destination network has been specified
	*/
	char netbuf[INIClass::MAX_LINE_LENGTH];
	memset(netbuf, 0, sizeof(netbuf));
	char * netptr = netbuf; // level-2 1.001: INFERRED (RA1 form); its frame slot sits above netbuf
	bool found = ConfigINI.Get_String("Network", "DestNet", 0, netbuf, sizeof(netbuf)) ? true : false; // level-2 1.001: INFERRED name (RA1)
	if (found && netptr != NULL && strlen(netbuf)) {
		NetNumType net;
		NetNodeType node;

		/*
		** Scan the string, pulling off each address piece
		*/
		int i = 0;
		char * p = strtok(netbuf, "."); // level-2 1.001: the whole string is scanned
		int x; // level-2 1.001: INFERRED, declared at this level as in RA1 (gives the 1.001 x and i slots)
		while (p != NULL) {
			sscanf(p, "%x", &x);			// convert from hex string to int
			if (i < 4) {
				net[i] = (char)x;			// fill NetNum
			} else {
				node[i-4] = (char)x;		// fill NetNode
			}
			i++;
			p = strtok(NULL, ".");
		}

		/*
		** If all the address components were successfully read, fill in the
		** BridgeNet with a broadcast address to the network across the bridge.
		*/
		if (i >= 4) {
			Session.IsBridge = 1;
			memset(node, 0xff, 6);
			Session.BridgeNet = IPXAddressClass(net, node);
		}
	}
}
