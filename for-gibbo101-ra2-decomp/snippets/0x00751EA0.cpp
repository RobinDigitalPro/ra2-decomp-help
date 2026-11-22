// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00751EA0 (369 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x309ec0 (VA 0x00709EC0, 384 bytes incl. padding)
// RA2 symbol : ?CountFiles@@YIXPBDAAI11@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9421)
// source TU  : src/m85/src/volinfo.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Counts the files and directories beneath a path.
/// This routine walks the whole directory tree under the search path and adds what it
/// finds to the supplied totals.
/// </summary>
/// <param name="path">The wildcard search path to scan, as handed to FindFirstFile.</param>
/// <remarks>The totals are added to rather than assigned, so clear them before the
/// first call.</remarks>
inline void CountFiles(char const * path, unsigned int & dircount, unsigned int & filecount, unsigned int & size)
{
	HANDLE handle;
	char filename[260];
	WIN32_FIND_DATA finddata;

	handle = FindFirstFile(path, &finddata);
	if (handle != INVALID_HANDLE_VALUE) {
		do {

			if (finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

				/// FindFirstFile will always return "." and ".." as first two dirs
				if (strcmpi(finddata.cFileName, ".") == 0) continue;
				if (strcmpi(finddata.cFileName, "..") == 0) continue;

				dircount++;
				strcpy(filename, path);

				filename[strlen(filename) - 1] = '\0';

				strcat(filename, finddata.cFileName);
				strcat(filename, "\\*");

				CountFiles(filename, dircount, filecount, size);

			} else {

				filecount++;
				size += finddata.nFileSizeLow;
			}
		}

		while (FindNextFile(handle, &finddata));

		FindClose(handle);
	}
}
