// RA2 1.001 byte-identical (VC6 8168 /O2 /Ob2 /Gr /GR /Gy), RVA 0x120fd0, from our src/m85/src/ionblast.cpp. GPL-3.0-or-later.
// Your 1.006 entry 0x00521A90 (IonBlastClass::One_Time, 541 bytes, non_exact in your map).

void IonBlastClass::One_Time(void)
{
	static bool one_time = false;
	if (one_time) {
		return;
	}

	double min_dist = WaveStartDistance - WaveBandWidth;
	double max_dist = WaveStartDistance;

	for (int frame = 0; frame < ARRAY_SIZE(BlastSurfaces); frame++) {
		BlastSurfaces[frame] = new BSurface(256, 128, 1);
		BlastSurfaces[frame]->Fill(-1);

		// The blast centre is the middle of the surface.
		int x = 128;
		int y = 64;
		char * center = (char *)BlastSurfaces[frame]->Lock() + (y << 8) + x;

		// One quadrant is computed and mirrored into the other three; rows count double.
		for (y = 63; y >= 0; y--) {
			int y_dist_sq = y * y * 4;
			for (int i = 0; i <= 127; i++) {
				x = 127 - i;
				double dist = fastmath::sqrt(x * x + y_dist_sq);
				if (dist >= min_dist && dist <= max_dist) {
					double wave_height = (fastmath::sin((dist - frame * WavePhaseSpeed + 38.0) * WaveFrequency) * 3.5 + 3.0) / (dist / WaveAmplitudeFalloff + 1.0) + 0.5;
					char spiral_index = Point_To_Spiral_Index(Point2D(0, wave_height));
					int row = y << 8;
					center[row + x] = spiral_index;
					center[row - x] = spiral_index;
					center[-row + x] = spiral_index;
					center[-row - x] = spiral_index;
				}
			}
		}

		if (128.0 - WaveSpeed > max_dist) {
			max_dist += WaveSpeed;
		}

		min_dist = WaveSpeed * 1.2 + min_dist;

		if (min_dist > max_dist) {
			min_dist = max_dist;
		}
	}

	one_time = true;
}
