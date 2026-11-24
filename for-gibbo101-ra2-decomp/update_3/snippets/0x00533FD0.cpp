// ra2-decomp help snippet, update 2026-11-23 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00533FD0 (1137 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0x118a70 (VA 0x00518A70, 1118 bytes without padding)
// RA2 symbol : ?Allocate_Surfaces@@YI_NABV?$TRect@H@@000_N@Z
// similarity : 0.9770 (very-similar, masked instruction tokens; shape 0.9795)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/init.cpp
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

bool Allocate_Surfaces(const Rect & hidden_rect, const Rect & composite_rect, const Rect & tile_rect, const Rect & sidebar_rect, bool hidden_first) // RA2: 0x00519500; the composite and tile surfaces follow VideoBackBuffer, the sidebar surface AllowVRAMSidebar; compiles to the executable's 1120 bytes, but with the hidden and composite rectangles in the other two registers and the memory flags on the stack, so it is excepted
{
	DebugString("Allocating new surfaces\n");

	if (AlternateSurface != NULL) {
		DebugString("Deleting AlternateSurface\n");
		delete AlternateSurface;
		AlternateSurface = NULL;
	}

	if (HiddenSurface != NULL) {
		DebugString("Deleting HiddenSurface\n");
		delete HiddenSurface;
		HiddenSurface = NULL;
	}

	if (CompositeSurface != NULL) {
		DebugString("Deleting CompositeSurface\n");
		delete CompositeSurface;
		CompositeSurface = NULL;
	}

	if (TileSurface != NULL) {
		DebugString("Deleting TileSurface\n");
		delete TileSurface;
		TileSurface = NULL;
	}

	if (SidebarSurface != NULL) {
		DebugString("Deleting SidebarSurface\n");
		delete SidebarSurface;
		SidebarSurface = NULL;
	}

	bool tile_in_system = !VideoBackBufferAllowed; // RA2: the composite and tile surfaces go to system memory unless the video back buffer is allowed
	bool sidebar_in_system = !Options.AllowVRAMSidebar; // RA2: as above for the sidebar surface

	if (hidden_first && hidden_rect.Is_Valid()) {
		HiddenSurface = new DSurface(hidden_rect.Width, hidden_rect.Height, false); // RA2: as above
		HiddenSurface->Fill(0);

		DebugString("HiddenSurface (%dx%d) %s\n", hidden_rect.Width, hidden_rect.Height,
					((DSurface *)HiddenSurface)->In_Video_Ram() ? "VRAM" : "SYSTEM MEMORY");
	}

	if (composite_rect.Is_Valid()) {
		CompositeSurface = new DSurface(composite_rect.Width, composite_rect.Height, Memory_Flag(tile_in_system)); // RA2: as above
		CompositeSurface->Fill(0);

		DebugString("CompositeSurface (%dx%d) %s\n", composite_rect.Width, composite_rect.Height,
					((DSurface *)CompositeSurface)->In_Video_Ram() ? "VRAM" : "SYSTEM MEMORY");
	}

	if (tile_rect.Is_Valid()) {
		TileSurface = new DSurface(tile_rect.Width, tile_rect.Height, Memory_Flag(tile_in_system)); // RA2: as above
		TileSurface->Fill(0);

		DebugString("TileSurface (%dx%d) %s\n", tile_rect.Width, tile_rect.Height,
					((DSurface *)TileSurface)->In_Video_Ram() ? "VRAM" : "SYSTEM MEMORY");
	}

	if ((CompositeSurface != NULL) && (TileSurface != NULL)) {
		bool is_composite_surf_in_vram = ((DSurface *)CompositeSurface)->In_Video_Ram();
		bool is_tile_surf_in_vram = ((DSurface *)TileSurface)->In_Video_Ram();

		if (is_composite_surf_in_vram ^ is_tile_surf_in_vram) {
			delete CompositeSurface;
			delete TileSurface;
			DebugString("Moving TileSurface and CompositeSurface into system memory\n");
			CompositeSurface = new DSurface(composite_rect.Width, composite_rect.Height, true);
			TileSurface = new DSurface(tile_rect.Width, tile_rect.Height, true);
		}
	}

	if (sidebar_rect.Is_Valid()) {
		SidebarSurface = new DSurface(sidebar_rect.Width, sidebar_rect.Height, Memory_Flag(sidebar_in_system)); // RA2: as above
		SidebarSurface->Fill(0);

		DebugString("SidebarSurface (%dx%d) %s\n", sidebar_rect.Width, sidebar_rect.Height,
					((DSurface *)SidebarSurface)->In_Video_Ram() ? "VRAM" : "SYSTEM MEMORY");
	}

	if (!hidden_first && hidden_rect.Is_Valid()) {
		HiddenSurface = new DSurface(hidden_rect.Width, hidden_rect.Height, false); // RA2: as above
		HiddenSurface->Fill(0);

		DebugString("HiddenSurface (%dx%d) %s\n", hidden_rect.Width, hidden_rect.Height,
					((DSurface *)HiddenSurface)->In_Video_Ram() ? "VRAM" : "SYSTEM MEMORY");
	}

	if (hidden_rect.Is_Valid()) {
		AlternateSurface = new DSurface(hidden_rect.Width, hidden_rect.Height, true);
		AlternateSurface->Fill(0);

		DebugString("AlternateSurface (%dx%d) %s\n", hidden_rect.Width, hidden_rect.Height,
					((DSurface *)AlternateSurface)->In_Video_Ram() ? "VRAM" : "SYSTEM MEMORY");
	}

	return(true);
}
