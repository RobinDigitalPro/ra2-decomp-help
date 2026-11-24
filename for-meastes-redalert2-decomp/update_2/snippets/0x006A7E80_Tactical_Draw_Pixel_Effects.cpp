// RA2 1.001 byte-identical (VC6 8168 /O2 /Ob2 /Gr /GR /Gy), RVA 0x29d4c0, from our src/m85/src/tactical.cpp. GPL-3.0-or-later.
// Your 1.006 entry 0x006A7E80 (Tactical::Draw_Pixel_Effects, 954 bytes, non_exact in your map).

void Tactical::Draw_Pixel_Effects(Rect const & area, Rect const & cliprect) // RA2: not in TibSun, at 0x6A7E80
{
	// level-2 1.001: body ported from gibbo101/ra2-decomp @232414dc36 src/tactical.cpp (GPL-3.0-or-later)
	static unsigned _lasttime;
	Point2DStruct pixel = {0, 0};

	if (FPSCounter::CurrentFrameRate >= Detail::GetMinFrameRate() && LogicalSurface->Bytes_Per_Pixel() == 2 && Options.DetailLevel != 0) {
		unsigned short * buffer = (unsigned short *)LogicalSurface->Lock();
		if (buffer != NULL) {
			unsigned now = timeGetTime();
			unsigned elapsed = now - _lasttime;
			_lasttime = now;
			if (elapsed > 1000) {
				elapsed = 1000;
			}
			int pitch = LogicalSurface->Stride();

			Point2D lepton = Pixel_To_Lepton(area.Top_Left() + Point2D(TacPixelX, TacPixelY) - TacticalRect.Top_Left());
			Cell base = Cell(lepton.X / CELL_LEPTON_W, lepton.Y / CELL_LEPTON_H);

			int ycount = area.Height / (ISO_TILE_PIXEL_H / 2) + 17;
			int xcount = area.Width / ISO_TILE_PIXEL_W + 4;

			base.X -= 2;
			Cell cell;
			int ix, iy;
			for (iy = 0; iy < ycount; iy++) {
				Cell step(iy / 2, (iy + 1) / 2);
				cell = base + step;

				for (ix = xcount; ix > 0; ix--) {
					if (Map.In_Radar(cell)) {
						CellClass * cellptr = &Map[cell];
						int value = cellptr->Tiberium_Value();
						if (cellptr->IsVisible && !cellptr->Is_Shrouded() && (cellptr->Land_Type() == LAND_WATER || value != 0) && cellptr->Cell_Occupier() == NULL && !cellptr->IsBridgeSurface) {
							PixelFXClass * fx = cellptr->PixelFX;
							int type = (value != 0);
							if (fx == NULL) {
								fx = new PixelFXClass(type);
								cellptr->PixelFX = fx;
							} else {
								if (fx->Phase >= 0x2000) {
									fx->Init(type);
								}
							}
							if (fx != NULL && fx->Expire(elapsed)) {
								Rect render = cellptr->Cell_Render_Rect();
								pixel.X = render.X + render.Width / 2;
								pixel.Y = render.Y + render.Height / 2;
								pixel.X += fx->OffsetX;
								pixel.Y += fx->OffsetY;
								if (cliprect.Is_Point_Within(Point2D(pixel))) {
									fx->Update(elapsed);
									((unsigned short *)((char *)buffer + pixel.Y * pitch))[pixel.X] = DSurface::Build_Hicolor_Pixel(fx->Current[0], fx->Current[1], fx->Current[2]);
								}
							}
						}
					}
					++cell.X;
					--cell.Y;
				}
			}
			LogicalSurface->Unlock();
		}
	}
}
