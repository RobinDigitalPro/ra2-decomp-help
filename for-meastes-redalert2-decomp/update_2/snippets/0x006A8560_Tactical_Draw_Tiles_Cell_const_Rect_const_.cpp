// RA2 1.001 byte-identical (VC6 8168 /O2 /Ob2 /Gr /GR /Gy), RVA 0x29d1e0, from our src/m85/src/tactical.cpp. GPL-3.0-or-later.
// Your 1.006 entry 0x006A8560 (Tactical::Draw_Tiles(Cell const &, Rect const &), 824 bytes, non_exact in your map).

void Tactical::Draw_Tiles(Rect const & area, Rect const & cliprect)
{
	Point2D point = Pixel_To_Ground_Point(PixelToCoordMatrix, area.Top_Left() + Point2D(TacPixelX, TacPixelY) - TacticalRect.Top_Left()); // RA2: Draw_Tiles at 0x6A7BA0 matches only so
	Coord lepton(point.X, point.Y, 0); // RA2: as above
	Cell origin(lepton.X / CELL_LEPTON_W, lepton.Y / CELL_LEPTON_H); // RA2: as above
	Cell base = origin; // RA2: as above

	int ycount = area.Height / (ISO_TILE_PIXEL_H / 2) + 17;
	int xcount = area.Width / ISO_TILE_PIXEL_W + 4;

	base.X -= 2; // RA2: as above
	int ix, iy;
	for (iy = 0; iy < ycount; iy++) {
		Cell step(iy / 2, (iy + 1) / 2);
		Cell cell = base + step;

		for (ix = xcount; ix > 0; ix--) {
			if (Map.In_Radar(cell)) {
				CellClass * cellptr = &Map[cell];
				Rect render = cellptr->Cell_Render_Rect();
				Rect inter = Intersect(area, render);
				Point2D pixel; // RA2: Draw_Tiles at 0x6A7BA0 has no Coord
				Project_Tile_Left(*this, Coord_Whole(Coord(cell)), pixel); // RA2: as above
				if (render.Is_Valid() && inter.Is_Valid()) {
					cellptr->Draw_It(pixel, cliprect, 0);
				}
			}
			cell += Cell(1, -1);
		}
	}
}
