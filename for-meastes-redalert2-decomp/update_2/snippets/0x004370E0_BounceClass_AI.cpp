// RA2 1.001 byte-identical (VC6 8168 /O2 /Ob2 /Gr /GR /Gy), RVA 0x36f60, from our src/m85/src/bounce.cpp. GPL-3.0-or-later.
// Your 1.006 entry 0x004370E0 (BounceClass::AI, 1448 bytes, non_exact in your map).

BounceResultType BounceClass::AI(void)
{
	BounceResultType bounce_result = BOUNCE_MOVING;

	/*
	 * Remember the pre-move position and velocity so the off-cliff handler can
	 * restore them. The saved velocity is the value before gravity is applied below.
	 */
	Vector3 & position = MyCoord;
	Vector3 & velocity = Velocity;
	Vector3 old_position = position;
	Vector3 old_velocity = velocity;
	if (Ballistic_Move(position, velocity, Gravity, Elasticity, MaxVelocity)) { // level-2 1.001: the shared step (1.001 calls the Vector3 and Coord inlines exactly as its inlined sequence does)
		/*
		 * Invert the spin axis of the angular velocity (but not the W component).
		 */
		AngularVelocity[0] = -AngularVelocity[0];
		AngularVelocity[1] = -AngularVelocity[1];
		AngularVelocity[2] = -AngularVelocity[2];

		/*
		 * If the object fell off a cliff edge, restore its pre-move state and bounce
		 * off the slope of the cell it would have fallen into.
		 */
		{
			Coord impact_coord(MyCoord.X, MyCoord.Y, MyCoord.Z);
			Coord previous_impact_coord(old_position.X, old_position.Y, old_position.Z);
			int previous_cell_height = Map[(Coord const &)previous_impact_coord].Height;
			if (Map[(Coord const &)impact_coord].Height - previous_cell_height >= 2) {
				if (old_velocity.Z < -0.0002 && MyCoord.Z > old_position.Z
					|| old_velocity.Z >= -0.0003 && (old_velocity.Z + old_position.Z + 1.0f < MyCoord.Z)) {

					position = old_position;
					velocity = old_velocity;

					FacingType bounce_facing = Map[(Coord const &)impact_coord].Bounce_Direction((Coord const &)previous_impact_coord);
					if (bounce_facing != FACING_NONE) {
						Matrix3D bounce_matrix = Get_Bounce_Matrix(bounce_facing);
						velocity = bounce_matrix * velocity;
						velocity *= Elasticity;
					}
				}
			}
		}

		bounce_result = BOUNCE_IMPACT;
	}

	Rotation = Rotation * AngularVelocity;

	double remaining_motion = Get_Remaining_Motion();
	if (remaining_motion < 2.5) {
		bounce_result = BOUNCE_SETTLED;
	}
	return(bounce_result);
}
