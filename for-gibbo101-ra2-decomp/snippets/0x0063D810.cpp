// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0063D810 (252 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x212180 (VA 0x00612180, 256 bytes incl. padding)
// RA2 symbol : ?Planning_Draw_Line@@YIXVPoint2D@@0HH_N@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9783)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Draw_Line(Point2D start, Point2D end, int offset, int color, bool dashed) // RA2: 0x0061A5A0; draws a line on the tactical view moved sideways by offset (clipped to it), dashed or solid
{
	bool steep = abs(end.X - start.X) > abs(end.Y - start.Y); // RA2: as above
	int sideways = steep ? 0 : offset; // RA2: as above
	int lengthways = steep ? offset : 0; // RA2: as above
	start.X += sideways; // RA2: as above
	start.Y += lengthways; // RA2: as above
	end.X += sideways; // RA2: as above
	end.Y += lengthways; // RA2: as above
	Rect area = TacticalRect; // RA2: as above
	if (Clip_Line_To_Rect(start, end, area)) { // RA2: as above
		if (dashed) { // RA2: as above
			int phase = (-(int)timeGetTime() >> 5) & 0xF; // RA2: as above
			CompositeSurface->Draw_Dashed_Line(start, end, color, (bool *)PlanningDashes, phase); // RA2: as above
		} else { // RA2: as above
			CompositeSurface->Draw_Line(start, end, color); // RA2: as above
		}
	}
}
