// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00750AC0 (634 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x308af0 (VA 0x00708AF0, 640 bytes incl. padding)
// RA2 symbol : ?Volume_At@@YIMABVCoord@@PAHPAVAudioEventType@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9849)
// source TU  : src/m85/src/voc.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Plays a voice sound effect.
/// This routine is used for the spoken responses and announcements. Unlike a general
/// purpose sound effect, the volume is not scaled by the sound effect option setting.
/// </summary>
/// <param name="voc">The sound effect to play.</param>
/// <param name="volume">The volume to assign to this sound effect.</param>
/// <returns>Returns with the sound handle, or -1 if no sound was played.</returns>
/// <param name="coord">The world location the sound comes from.</param>
/// <param name="panning">Receives the panning, from 0 to 0x4000.</param>
/// <param name="type">The audio library's event type of the sound.</param>
/// <returns>Returns with the volume from 0 to 1, or 0 if the sound is not to be heard.</returns>
float __fastcall Volume_At(Coord const & coord, int * panning, AudioEventType * type) // RA2: a free function the sound effect routines share
{
	*panning = 0;
	float halfwidth = TacticalRect.Width * 0.5f; // RA2: as above
	float halfheight = TacticalRect.Height * 0.5f; // RA2: as above
	float volume = 0; // RA2: as above
	float width = halfwidth + halfwidth; // RA2: as above
	float range = AudioEventTypeRange(type) * 60; // RA2: the range in cells, 60 pixels each
	unsigned int flags = AudioEventTypeGetType(type); // RA2: as above
	if (flags & 0x800) { // RA2: sounds that only play where the player has seen
		Cell cell = Cell(coord.X / 256, coord.Y / 256); // RA2: as above
		if (cell == CELL_NONE) { // RA2: as above
			return(0); // RA2: as above
		}
		CellClass & cellptr = Map[cell]; // RA2: as above
		if (!cellptr.IsMapped && !cellptr.IsVisible) { // RA2: as above
			return(0); // RA2: as above
		}
	}

	Point2D pixel; // RA2: as above
	TacticalMap->Coord_To_Pixel(coord, pixel); // RA2: as above
	float dx = pixel.X - halfwidth; // RA2: as above
	float x = abs((int)dx); // RA2: as above
	float y = abs((int)(pixel.Y - halfheight)); // RA2: as above
	if (!(flags & 0x40)) { // RA2: as above
		x -= halfwidth; // RA2: as above
		y -= halfheight; // RA2: as above
		if (x < 0) { // RA2: as above
			x = 0; // RA2: as above
		}
		if (y < 0) { // RA2: as above
			y = 0; // RA2: as above
		}
	}
	y = y + y; // RA2: as above
	if (x < range && y < range && range > 0) { // RA2: as above
		float distance = x > y ? x : y; // RA2: as above
		volume = (range - distance) / range; // RA2: as above
	}
	if (flags & 0x10) { // RA2: as above
		if (AudioEventTypeMinVolume(type) > volume) { // RA2: as above
			volume = AudioEventTypeMinVolume(type); // RA2: as above
		}
	}
	if (volume < 0.05) { // RA2: as above
		return(0); // RA2: as above
	}

	if (dx < -width) { // RA2: as above
		dx = -width; // RA2: as above
	} else if (dx > width) { // RA2: as above
		dx = width; // RA2: as above
	}
	*panning = (int)(dx * 8192.0f / width + 8192.0f);
	return(volume); // RA2: as above
}
