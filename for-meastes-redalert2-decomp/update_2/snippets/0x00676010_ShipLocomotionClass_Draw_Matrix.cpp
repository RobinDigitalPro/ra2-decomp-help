// RA2 1.001 byte-identical (VC6 8168 /O2 /Ob2 /Gr /GR /Gy), RVA 0x26b990, from our src/m85/src/ship.cpp. GPL-3.0-or-later.
// Your 1.006 entry 0x00676010 (ShipLocomotionClass::Draw_Matrix, 1189 bytes, non_exact in your map).

Matrix3DStruct STDMETHODCALLTYPE ShipLocomotionClass::Draw_Matrix(int *key)
{
	Matrix3DStruct m;

	// level-2 1.001: STEERING Expand the angle test here so VC6 inlines the tilted path timer read.
	float percent = Get_Slope_Ratio();
	bool level = false;
	if (percent == 1.0) {
		if ((float)fabs(LinkedTo->AngleRotatedSideways) < 0.005 && (float)fabs(LinkedTo->AngleRotatedForwards) < 0.005) {
			level = true;
		}
	}
	if (!level) {
		Matrix3D m1, m2;
		m1.Make_Identity();
		m2.Make_Identity();

		float val = LinkedTo->TClass->VoxelCenterY;
		float val2 = LinkedTo->TClass->VoxelCenterX;

		float fcos = fastmath::cos(LinkedTo->AngleRotatedForwards);
		float fsin = fastmath::sin(LinkedTo->AngleRotatedForwards);

		float scos = fastmath::cos(LinkedTo->AngleRotatedSideways);
		float ssin = fastmath::sin(LinkedTo->AngleRotatedSideways);

		int num = fabs(ssin) * val + fabs(fsin) * val2;

		// level-2 1.001: the offsets are negated in place (hover.cpp form)
		int x_offset = (int)(val2 - (float)(int)(fcos * val2));
		int y_offset = (int)(val - (float)(int)(scos * val));
		if (LinkedTo->AngleRotatedForwards < 0.0f) {
			x_offset = -x_offset;
		}
		if (LinkedTo->AngleRotatedSideways > 0.0f) {
			y_offset = -y_offset;
		}

		m1.Translate_Z(num);
		m2.Translate_X(x_offset);
		m2.Translate_Y(y_offset);
		m2.Rotate_X(LinkedTo->AngleRotatedSideways);
		m2.Rotate_Y(LinkedTo->AngleRotatedForwards);

		if (key) {
			*key = -1;
		}

		// level-2 1.001: one expression (no temporary is reused), the slope matrix is fetched inside it
		m = (Matrix3DStruct &)(((m1 * Get_Slope_Matrix()) * BASECLASS::Draw_Matrix(key)) * m2);
	} else { // level-2 1.001: if/else with one return; both branches share their stack slots
		if (key && *key != -1) {
			*key <<= 6; // level-2 1.001: updated in place
			*key += CurrentRamp;
		}
		m = (Matrix3DStruct &)(Get_Slope_Matrix() * BASECLASS::Draw_Matrix(key));
	}
	return(m);
}
