// RA2 1.001 byte-identical (VC6 8168 /O2 /Ob2 /Gr /GR /Gy), RVA 0x7a900, from our src/m85/src/cell.cpp. GPL-3.0-or-later.
// Your 1.006 entry 0x0047AD00 (CellClass::Place_Veins, 2191 bytes, non_exact in your map).

void CellClass::Place_Veins(void)
{
	Rect rect(0, 0, 0, 0);

	if (Can_Place_Veins()) {

		rect = Union(rect, Union(Overlay_Render_Rect(), Overlay_Shadow_Render_Rect()));

		Map.Radar_Background(CellID);
		Overlay = OVERLAY_VEINS;

		if (Ramp == RAMP_NONE) {
			OverlayData = abs(Scen->RandomNumber()) % 3 + OVERLAYDATA_FIRST_SOLID_VEIN;

			for (int dir = FACING_N; dir < FACING_COUNT; dir += FACING_90) {
				CellClass & adjacent = Adjacent_Cell(FacingType(dir));

				if (adjacent.Overlay == OVERLAY_VEINS && adjacent.OverlayData >= OVERLAYDATA_FIRST_SOLID_VEIN) {
					continue;
				}
				if (adjacent.Overlay != OVERLAY_VEINS && adjacent.Overlay != OVERLAY_NONE && OverlayTypes[adjacent.Overlay]->IsVeins) {
					continue;
				}

				if (adjacent.Ramp == RAMP_NONE) {
					int frame = _Vein_Frame_B(&adjacent); // level-2 1.001: STEERING retain the out-of-line Get_Vein_Frame call.
					if (adjacent.Overlay == OVERLAY_NONE || (frame <= 15 && adjacent.OverlayData / 3 != frame)) {
						Rect adjrect(0, 0, 0, 0);
						adjrect = Union(adjrect, Union(adjacent.Overlay_Render_Rect(), adjacent.Overlay_Shadow_Render_Rect()));
						adjacent.Overlay = OVERLAY_VEINS;
						adjacent.OverlayData = 3 * frame + abs(Scen->RandomNumber % 3);
						adjacent.Recalc_Attributes();
						Point2D origin = TacticalRect.TopLeft;
						adjrect = Union(adjrect, Union(adjacent.Overlay_Render_Rect(), adjacent.Overlay_Shadow_Render_Rect())) - origin;
						TacticalMap->Register_Dirty_Area(adjrect);
					}
				} else {
					Rect adjrect(0, 0, 0, 0);
					adjrect = Union(adjrect, Union(adjacent.Overlay_Render_Rect(), adjacent.Overlay_Shadow_Render_Rect()));
					adjacent.Overlay = OVERLAY_VEINS;
					adjacent.OverlayData = 2 * adjacent.Ramp + (abs(Scen->RandomNumber()) & 1) + OVERLAYDATA_FIRST_RAMP_VEIN;
					adjrect = Union(adjrect, Union(adjacent.Overlay_Render_Rect(), adjacent.Overlay_Shadow_Render_Rect())) - TacticalRect.TopLeft;
					TacticalMap->Register_Dirty_Area(adjrect);
				}

				Map.Radar_Background(adjacent.CellID);
			}

			Trigger_Veins();
		} else {
			OverlayData = 2 * Ramp + (abs(Scen->RandomNumber()) & 1) + OVERLAYDATA_FIRST_RAMP_VEIN;
		}

		rect = Union(rect, Union(Overlay_Render_Rect(), Overlay_Shadow_Render_Rect())) - TacticalRect.TopLeft;
		TacticalMap->Register_Dirty_Area(rect);
		Recalc_Attributes();
	}
}
