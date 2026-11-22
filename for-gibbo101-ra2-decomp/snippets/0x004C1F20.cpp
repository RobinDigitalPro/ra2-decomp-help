// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004C1F20 (2159 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xb1610 (VA 0x004B1610, 2160 bytes incl. padding)
// RA2 symbol : ?Draw_Bolt@EBolt@@QAEXVCoord@@0H@Z
// similarity : 0.9966 (very-similar, masked instruction tokens; shape 0.9992)
// source TU  : src/m85/src/ebolt.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Draws the bolt as three jagged lines (two in the bolt color, a white core in color 15) by halving the segment up to eight times and moving the midpoints at random.
/// </summary>
void EBolt::Draw_Bolt(Coord start, Coord end, int color) // RA2: 0x004B1900
{
	BoltSegment stack[8]; // RA2: as above
	Coord mids[3]; // RA2: as above
	Coord starts[3]; // RA2: as above
	Coord ends[3]; // RA2: as above
	int offsets[6]; // RA2: as above
	bool first = true; // RA2: as above
	int depth = 0; // RA2: as above

	int length = Bolt_Length5(start, end); // RA2: through the placeholder layers above; the executable calls TPoint3D's constructor here
	if (length != 0) { // RA2: as above
		int threshold = (length * 102) >> 8; // RA2: as above
		int deviation = (length * 23) >> 8; // RA2: as above
		int start_z = Unknown_18; // RA2: as above
		BoltSegment * seg = stack; // RA2: as above
		int end_z = 0; // RA2: as above
		for (int i = 0; i < 3; i++) { // RA2: as above
			starts[i] = start; // RA2: as above
			ends[i] = end; // RA2: as above
		} // RA2: as above

		for (;;) { // RA2: as above
			if (length > 64 && depth < 8) { // RA2: as above
				for (int j = 0; j < 3; j++) { // RA2: as above
					mids[j].X = (starts[j].X + ends[j].X) >> 1; // RA2: as above
					mids[j].Y = (starts[j].Y + ends[j].Y) >> 1; // RA2: as above
					mids[j].Z = (starts[j].Z + ends[j].Z) >> 1; // RA2: as above
				} // RA2: as above
				if (first) { // RA2: as above
					first = false; // RA2: as above
					double dev = deviation; // RA2: as above
					for (int k = 0; k < 6; k++) { // RA2: as above
						offsets[k] = fastmath::sin(Random * 3.141592653589793 / (k + 7)) * dev; // RA2: fastmath::sin (0x004BA480) instead of the intrinsic
					} // RA2: as above
					int zoff = (offsets[2] + offsets[4] + deviation * 2) >> 1; // RA2: as above
					for (int m = 0; m < 3; m++) { // RA2: as above
						mids[m].X += offsets[0] + offsets[3]; // RA2: as above
						mids[m].Y += offsets[1] + offsets[5]; // RA2: as above
						mids[m].Z += zoff; // RA2: as above
					} // RA2: as above
				} // RA2: as above
				if (length <= 128) { // RA2: as above
					mids[0].X += NonCriticalRandomNumber(-1, 1) * deviation * 2; // RA2: as above
					mids[0].Y += NonCriticalRandomNumber(-1, 1) * deviation * 2; // RA2: as above
					mids[0].Z += NonCriticalRandomNumber(-1, 1) * deviation * 2; // RA2: as above
				} else { // RA2: as above
					mids[0].X += NonCriticalRandomNumber(-deviation, deviation); // RA2: as above
					mids[0].Y += NonCriticalRandomNumber(-deviation, deviation); // RA2: as above
					mids[0].Z += NonCriticalRandomNumber(-deviation, deviation); // RA2: as above
				} // RA2: as above
				if (length > threshold) { // RA2: as above
					for (int n = 1; n < 3; n++) { // RA2: as above
						mids[n].X = mids[0].X + (NonCriticalRandomNumber(-deviation, deviation) >> 1); // RA2: as above
						mids[n].Y = mids[0].Y + (NonCriticalRandomNumber(-deviation, deviation) >> 1); // RA2: as above
						mids[n].Z = mids[0].Z + (NonCriticalRandomNumber(-deviation, deviation) >> 1); // RA2: as above
					} // RA2: as above
				} else { // RA2: as above
					for (int n2 = 1; n2 < 3; n2++) { // RA2: as above
						mids[n2].X += NonCriticalRandomNumber(-deviation, deviation); // RA2: as above
						mids[n2].Y += NonCriticalRandomNumber(-deviation, deviation); // RA2: as above
						mids[n2].Z += NonCriticalRandomNumber(-deviation, deviation); // RA2: as above
					} // RA2: as above
				} // RA2: as above
				length >>= 1; // RA2: as above
				deviation >>= 1; // RA2: as above
				int mid_z = (end_z + start_z) >> 1; // RA2: as above
				for (int p = 0; p < 3; p++) { // RA2: as above
					seg->Start[p] = mids[p]; // RA2: as above
					seg->End[p] = ends[p]; // RA2: as above
				} // RA2: as above
				seg->Length = length; // RA2: as above
				seg->Deviation = deviation; // RA2: as above
				seg->StartDepth = mid_z; // RA2: as above
				seg->EndDepth = end_z; // RA2: as above
				seg++; // RA2: as above
				depth++; // RA2: as above
				memcpy(ends, mids, sizeof(ends)); // RA2: as above
				end_z = mid_z; // RA2: as above
			} else { // RA2: as above
				Draw_Line(starts[1], ends[1], color, start_z, end_z); // RA2: as above
				Draw_Line(starts[2], ends[2], color, start_z, end_z); // RA2: as above
				Draw_Line(starts[0], ends[0], 15, start_z, end_z); // RA2: as above
				if (--depth < 0) break; // RA2: as above
				seg--; // RA2: as above
				memcpy(ends, seg->End, sizeof(ends)); // RA2: as above
				memcpy(starts, seg->Start, sizeof(starts)); // RA2: as above
				length = seg->Length; // RA2: as above
				deviation = seg->Deviation; // RA2: as above
				start_z = seg->StartDepth; // RA2: as above
				end_z = seg->EndDepth; // RA2: as above
			} // RA2: as above
		} // RA2: as above
	} // RA2: as above
}
