// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x004BEAC0 (2951 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xae6d0 (VA 0x004AE6D0, 2960 bytes incl. padding)
// RA2 symbol : ?Draw_Trail_Line@DSurface@@QAE_NABV?$TRect@H@@AAVPoint2D@@1AAVRGBClass@@HHH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9944)
// source TU  : src/m85/src/dsurface.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool DSurface::Draw_Trail_Line(Rect const & cliprect, Point2D & startpoint, Point2D & endpoint, RGBClass & color, int alpha, int start_height, int end_height) // RA2: not in TibSun, at 0x4AE9C0
{
	Point2D start;
	Point2D end;

	if (alpha >= 8) {

	Rect rect = Intersect(cliprect, Get_Rect());
	if (rect.Width != 0 || rect.Height != 0) {

	start = Bias_To(startpoint, rect);
	end = Bias_To(endpoint, rect);

	int z2 = end_height;
	int z1 = start_height;
	if (start.X > end.X) {
		swap(start, end);
		z1 = end_height;
		z2 = start_height;
	}

	Point2D origend = end;
	int px = start.X;
	int py = start.Y;

	if (Clip_Line_To_Rect(start, end, rect)) {

	int zend = z2;
	int zstart = z1;

	if (end.X != origend.X || end.Y != origend.Y) {
		int amount = abs((int)((double)Distance(Point2D(px, py), end) / (double)Distance(Point2D(px, py), origend) * (double)(z1 - z2)));
		if (z1 < z2) {
			zend = z1 + amount;
		} else {
			zend = z1 - amount;
		}
	}

	if (start.X != px || start.Y != py) {
		int amount = abs((int)((double)Distance(start, origend) / (double)Distance(Point2D(px, py), origend) * (double)(z1 - z2)));
		if (z2 > z1) {
			zstart = z2 - amount;
		} else {
			zstart = z2 + amount;
		}
	}

	Bytes_Per_Pixel();
	void * buffer = Lock(start);

	if (DepthBuffer != NULL) {

	Point2D point = start;
	point.Y -= DepthBuffer->Get_Bounds().Y;
	unsigned short * zbuffer = (unsigned short *)DepthBuffer->Get_Buffer_Offset(point);
	point = start;
	point.Y -= AlphaBuffer->Get_Bounds().Y;
	unsigned short * abuffer = (unsigned short *)AlphaBuffer->Get_Buffer_Offset(point);

	int start_y = start.Y;
	int zwrap = -1;
	ZBuffer * depth_buffer = DepthBuffer;
	unsigned short z = (unsigned short)(zstart + (short)(depth_buffer->Get_Bounds().Y + depth_buffer->Get_Scroll()) - start_y - rect.Y);
	int zwidth = DepthBuffer->Get_Buffer_Width();

	if (buffer != NULL) {

	int red = (color.Get_Red() * alpha) >> 8;
	int green = (color.Get_Green() * alpha) >> 8;
	int blue = (color.Get_Blue() * alpha) >> 8;
	int inv_alpha = 256 - alpha;

	int dx = end.X - start.X;
	int dy = end.Y - start.Y;
	int dz = zend - zstart;

	int pitch = Stride();
	if (dy < 0) {
		pitch = -pitch;
		zwidth = -zwidth;
		zwrap = 1;
	}

	int abs_dy = abs(dy);
	int zstep = 1;
	if (dz < 0) {
		zstep = -1;
	}

	int abs_dz = abs(dz);
	int dx2 = 2 * dx;
	int dy2 = 2 * abs_dy;
	int dz2 = 2 * abs_dz;

	if (abs_dz > dx && abs_dz > abs_dy) {

		int xdelta = dy2 - abs_dz;
		int ydelta = dx2 - abs_dz;
		if (abs_dz > 0) {
			int offset = 0;
			for (int i = abs_dz; i != 0; i--) {

				int v = *abuffer;
				if (z < *zbuffer && v != 0) {
					RGBClass rgb = Deconstruct_Hicolor_Pixel(*(unsigned short *)((char *)buffer + offset));
					*(unsigned short *)((char *)buffer + offset) = (unsigned short)Alpha_Hicolor_Pixel(rgb, v, inv_alpha, red, green, blue);
				}

				if (xdelta > 0) {
					buffer = (unsigned char *)buffer + pitch;
					xdelta -= dz2;
					zbuffer += zwidth;
					if (zwidth > 0) {
						zbuffer = Blit_Wrap_Z_Buffer(zbuffer);
					} else {
						zbuffer = (unsigned short *)DepthBuffer->Wrap_Underflow((unsigned int)zbuffer);
					}
					abuffer += zwidth;
					if (zwidth > 0) {
						abuffer = Blit_Wrap_A_Buffer(abuffer);
					} else {
						abuffer = (unsigned short *)AlphaBuffer->Wrap_Underflow((unsigned int)abuffer);
					}
					z += zwrap;
				}

				if (ydelta > 0) {
					zbuffer++;
					offset += 2;
					zbuffer = Blit_Wrap_Z_Buffer(zbuffer);
					abuffer++;
					abuffer = Blit_Wrap_A_Buffer(abuffer);
					ydelta -= dz2;
				}

				z += zstep;
				ydelta += dx2;
				xdelta += dy2;
			}
		}
	} else if (dx > abs_dy) {

		int ydelta = dy2 - dx;
		int zdelta = dz2 - dx;
		int i = 0;
		if (dx > 0) {
			for (; i < dx; i++) {

				int v = *abuffer;
				if (z < *zbuffer && v != 0) {
					RGBClass rgb = Deconstruct_Hicolor_Pixel(*((unsigned short *)buffer + i));
					*((unsigned short *)buffer + i) = (unsigned short)Alpha_Hicolor_Pixel(rgb, v, inv_alpha, red, green, blue);
				}

				if (ydelta > 0) {
					buffer = (unsigned char *)buffer + pitch;
					ydelta -= 2 * dx;
					zbuffer += zwidth;
					if (zwidth > 0) {
						zbuffer = Blit_Wrap_Z_Buffer(zbuffer);
					} else {
						zbuffer = (unsigned short *)DepthBuffer->Wrap_Underflow((unsigned int)zbuffer);
					}
					z += zwrap;
					abuffer += zwidth;
					if (zwidth > 0) {
						abuffer = Blit_Wrap_A_Buffer(abuffer);
					} else {
						abuffer = (unsigned short *)AlphaBuffer->Wrap_Underflow((unsigned int)abuffer);
					}
				}

				if (zdelta > 0) {
					z += zstep;
					zdelta -= 2 * dx;
				}

				zbuffer++;
				ydelta += dy2;
				zdelta += dz2;
				zbuffer = Blit_Wrap_Z_Buffer(zbuffer);
				abuffer++;
				abuffer = Blit_Wrap_A_Buffer(abuffer);
			}
		}
	} else {

		int xdelta = dx2 - abs_dy;
		int zdelta = dz2 - abs_dy;
		if (abs_dy > 0) {
			int offset = 0;
			for (int i = abs_dy; i != 0; i--) {

				int v = *abuffer;
				if (z < *zbuffer && v != 0) {
					RGBClass rgb = Deconstruct_Hicolor_Pixel(*(unsigned short *)((char *)buffer + offset));
					*(unsigned short *)((char *)buffer + offset) = (unsigned short)Alpha_Hicolor_Pixel(rgb, v, inv_alpha, red, green, blue);
				}

				if (xdelta > 0) {
					zbuffer++;
					offset += 2;
					zbuffer = Blit_Wrap_Z_Buffer(zbuffer);
					abuffer++;
					abuffer = Blit_Wrap_A_Buffer(abuffer);
					xdelta -= dy2;
				}

				if (zdelta > 0) {
					z += zstep;
					zdelta -= dy2;
				}

				xdelta += dx2;
				zdelta += dz2;
				buffer = (unsigned char *)buffer + pitch;

				zbuffer += zwidth;
				if (zwidth > 0) {
					zbuffer = Blit_Wrap_Z_Buffer(zbuffer);
				} else {
					zbuffer = (unsigned short *)DepthBuffer->Wrap_Underflow((unsigned int)zbuffer);
				}
				z += zwrap;
				abuffer += zwidth;
				if (zwidth > 0) {
					abuffer = Blit_Wrap_A_Buffer(abuffer);
				} else {
					abuffer = (unsigned short *)AlphaBuffer->Wrap_Underflow((unsigned int)abuffer);
				}
			}
		}
	}

	Unlock();
	return(true);

	}
	}
	}
	}
	}

	return(false);
}
