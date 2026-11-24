// RA2 1.001 byte-identical (VC6 8168 /O2 /Ob2 /Gr /GR /Gy), RVA 0x1f1c0, from our src/m85/src/alphashp.cpp. GPL-3.0-or-later.
// Your 1.006 entry 0x0041F1C0 (AlphaShapeClass::Draw_In_Area, 1048 bytes, non_exact in your map).

void AlphaShapeClass::Draw_In_Area(Point2D const & point, Rect const & cliprect)
{
	/// The table is spelled with literal 0x20 (space) and 0xDB (solid block) characters,
	/// written as escapes here so that it survives text encoding conversions.
	#define __ "\x20"
	#define XX "\xDB"

	// level-2 1.001: the mask covers the full 60x30 tile (1.006 table was 48x24)
	static const unsigned char _tilemask[] = {
		__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __
		__ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __
		__ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __
		__ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __
		XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX
		__ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __
		__ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __
		__ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __
		__ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __
		__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ XX XX XX XX __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __
	};

	#undef __
	#undef XX

	for (int i = 0; i < AlphaShapes.Count(); i++) {
		if (!AlphaShapes[i]->IsToDelete) {
			Rect r1 = AlphaShapes[i]->DrawRect;
			r1 -= Point2D(TacticalMap->TacPixelX, TacticalMap->TacPixelY);
			r1 += TacticalRect.Top_Left();

			Rect r2 = Intersect(r1, cliprect);
			Rect r3(point.X, point.Y, ISO_TILE_PIXEL_W, ISO_TILE_PIXEL_H);
			Rect r4 = Intersect(r2, r3);

			if (r4.Is_Valid()) {
				// level-2 1.001: Point2D offset/origin locals (gibbo101 YR form)
				Point2D offset = r4.Top_Left() - r3.Top_Left();

				Point2D origin = r1.Top_Left();
				ShapeSet const * shape = AlphaShapes[i]->ImageData;
				Rect shape_rect = shape->Get_Rect(0);

				int top = MAX(r4.Y, shape_rect.Y + origin.Y);
				int src_y = top - origin.Y - shape_rect.Y;
				int bottom = MIN(r4.Y + r4.Height, origin.Y + shape_rect.Height + shape_rect.Y);
				int left = MAX(r4.X, shape_rect.X + origin.X);
				int src_x = left - origin.X - shape_rect.X;
				int right = MIN(r4.X + r4.Width, origin.X + shape_rect.Width + shape_rect.X);

				int shape_skip = origin.X - right + shape_rect.Width + src_x + shape_rect.X;
				int alpha_skip = AlphaBuffer->Get_Buffer_Width() - right + left;
				int mask_skip = ISO_TILE_PIXEL_W - r4.Width;

				const unsigned char * maskptr = &_tilemask[ISO_TILE_PIXEL_W * offset.Y + offset.X];
				unsigned char * shapeptr = (unsigned char *)shape->Get_Data(0);

				unsigned short * alphaptr = (unsigned short *)AlphaBuffer->Get_Buffer_Offset(Point2D(left, top - TacticalRect.Y));

				shapeptr += src_x + src_y * shape_rect.Width;
				unsigned char pixel;
				if (&alphaptr[right - left + (bottom - top) * AlphaBuffer->Get_Buffer_Width() + 2] >= (unsigned short *)AlphaBuffer->Get_Buffer_End()) {
					for (int i = top; i < bottom; i++) {
						for (int j = left; j < right; j++) {
							pixel = *shapeptr++;
							if (*maskptr++ != '\x20') {
								*alphaptr = BrightnessTable[pixel][*alphaptr];
							}
							alphaptr++;
							alphaptr = (unsigned short *)AlphaBuffer->Wrap_Overflow((unsigned)alphaptr);
						}
						shapeptr += shape_skip;
						maskptr += mask_skip;
						alphaptr += alpha_skip;
						alphaptr = (unsigned short *)AlphaBuffer->Wrap_Overflow((unsigned)alphaptr);
					}
				} else {
					for (int i = top; i < bottom; i++) {
						for (int j = left; j < right; j++) {
							pixel = *shapeptr++;
							if (*maskptr++ != '\x20') {
								*alphaptr = BrightnessTable[pixel][*alphaptr];
							}
							++alphaptr;
						}
						shapeptr += shape_skip;
						alphaptr += alpha_skip;
						maskptr += mask_skip;
					}
				}
			}
		}
	}
}
