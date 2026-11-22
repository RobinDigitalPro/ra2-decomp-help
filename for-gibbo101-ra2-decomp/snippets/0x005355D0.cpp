// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005355D0 (1167 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x119df0 (VA 0x00519DF0, 1168 bytes incl. padding)
// RA2 symbol : ?Get_Performance_Profile@@YIHXZ
// similarity : 0.9691 (very-similar, masked instruction tokens; shape 0.9522)
// source TU  : src/m85/src/init.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

int Get_Performance_Profile(void) // RA2: as above
{
	if (PerformanceProfile == -1) { // RA2: as above
		ProfileText[0] = 0; // RA2: as above
		ProfileCPUText[0] = 0; // RA2: as above
		ProfileRAMText[0] = 0; // RA2: as above
		ProfileVRAMText[0] = 0; // RA2: as above
		ProfileBlitText[0] = 0; // RA2: as above

		int type = Get_CPU_Type(); // RA2: as above
		int mhz = Get_RDTSC_CPU_Speed(); // RA2: as above
		int cpu = 5; // RA2: as above
		switch (type) { // RA2: as above
			case -1: // RA2: as above
				break;

			case 3:
			case 5: // RA2: as above
				cpu = mhz / 100 + 1; // RA2: as above
				break;

			case 4:
			case 7: // RA2: as above
				cpu = mhz / 100 + 2; // RA2: as above
				break;

			case 6: // RA2: as above
				cpu = mhz / 100 + 3; // RA2: as above
				break;

			default:
				cpu = 1; // RA2: as above
				break;
		}
		DebugString("Profile: CPU:%d (%dMhz %s)\n", cpu, mhz, Get_CPU_Type_Name()); // RA2: as above
		sprintf(ProfileCPUText, "CPU: %d Mhz %s", mhz, Get_CPU_Type_Name()); // RA2: as above

		MEMORYSTATUS status; // RA2: as above
		status.dwLength = sizeof(status); // RA2: as above
		GlobalMemoryStatus(&status); // RA2: as above
		int ram = 2; // RA2: as above
		unsigned int megabytes = (status.dwTotalPhys + 0xA0000) >> 20; // RA2: as above
		if (megabytes >= 64) { // RA2: as above
			ram = 5; // RA2: as above
		}
		if (megabytes >= 128) { // RA2: as above
			ram += 2; // RA2: as above
		}
		if (megabytes == 256) { // RA2: as above
			ram += 2; // RA2: as above
		} else if (megabytes > 256) { // RA2: as above
			ram = 10; // RA2: as above
		}
		DebugString("Profile: RAM:%d (%dMb)\n", ram, megabytes); // RA2: as above
		sprintf(ProfileRAMText, "RAM reported: %d Mb", megabytes); // RA2: as above

		megabytes = 4; // RA2: as above
		int vram = 5; // RA2: as above
		if (DirectDrawObject != NULL) { // RA2: as above
			DDCAPS caps; // RA2: as above
			caps.dwSize = sizeof(caps); // RA2: as above
			if (DirectDrawObject->GetCaps(&caps, NULL) == 0) { // RA2: as above
				unsigned int memory = caps.dwVidMemTotal > caps.dwVidMemFree ? caps.dwVidMemTotal : caps.dwVidMemFree; // RA2: as above
				megabytes = (memory + 0xFFFFF) >> 20; // RA2: as above
			}
		}
		if (megabytes >= 32) { // RA2: as above
			vram = 10; // RA2: as above
		} else if (megabytes >= 16) { // RA2: as above
			vram = 9; // RA2: as above
		} else if (megabytes >= 8) { // RA2: as above
			vram = 7; // RA2: as above
		} else if (megabytes >= 4) { // RA2: as above
			vram = 5; // RA2: as above
		} else if (megabytes <= 2) { // RA2: as above
			vram = 3; // RA2: as above
		}
		DebugString("Profile: VRAM:%d (%dMb)\n", vram, megabytes); // RA2: as above
		sprintf(ProfileVRAMText, "VRAM reported: %d Mb", megabytes); // RA2: as above

		int speed = 5; // RA2: as above
		int blits = 0; // RA2: as above
		if (TileSurface != NULL && ((DSurface *)TileSurface)->In_Video_Ram() && !((DSurface *)AlternateSurface)->In_Video_Ram()) { // RA2: as above
			Rect area = TileSurface->Get_Rect(); // RA2: as above
			Rect other = AlternateSurface->Get_Rect(); // RA2: as above
			if (area.Width >= other.Width) { // RA2: as above
				area.Width = other.Width; // RA2: as above
			}
			if (area.Height >= other.Height) { // RA2: as above
				area.Height = other.Height; // RA2: as above
			}
			if (area.Width >= 480) { // RA2: as above
				area.Width = 480; // RA2: as above
			}
			if (area.Height >= 400) { // RA2: as above
				area.Height = 400; // RA2: as above
			}
			for (int index = 0; index < 4; index++) { // RA2: as above
				TileSurface->Blit_From(area, *AlternateSurface, area, false, true); // RA2: as above
				AlternateSurface->Blit_From(area, *TileSurface, area, false, true); // RA2: as above
				Sleep(0); // RA2: as above
			}
			DWORD start = timeGetTime(); // RA2: as above
			if ((start & 0xFF000000) != 0xFF) { // RA2: as above
				TileSurface->Blit_From(area, *AlternateSurface, area, false, true); // RA2: as above
				AlternateSurface->Blit_From(area, *TileSurface, area, false, true); // RA2: as above
				blits++; // RA2: as above
				while (timeGetTime() - start <= 1000 && blits <= 5000) { // RA2: as above
					TileSurface->Blit_From(area, *AlternateSurface, area, false, true); // RA2: as above
					AlternateSurface->Blit_From(area, *TileSurface, area, false, true); // RA2: as above
					blits++; // RA2: as above
				}
				speed = blits / 4 < 1 ? 1 : blits / 4; // RA2: as above
			}
		}
		DebugString("Profile: VRAM speed:%d (%d blits per second)\n", speed, blits * 2); // RA2: as above
		sprintf(ProfileBlitText, "%d blits per second\n", blits * 2); // RA2: as above

		PerformanceProfile = cpu; // RA2: as above
		if (PerformanceProfile >= ram) { // RA2: as above
			PerformanceProfile = ram; // RA2: as above
		}
		if (PerformanceProfile >= vram) { // RA2: as above
			PerformanceProfile = vram; // RA2: as above
		}
		if (PerformanceProfile >= speed) { // RA2: as above
			PerformanceProfile = speed; // RA2: as above
		}
		DebugString("Overall performance profile = %d\n", PerformanceProfile); // RA2: as above
		sprintf(ProfileText, "Profile: %d\n", PerformanceProfile); // RA2: as above
	}
	return(PerformanceProfile); // RA2: as above
}
