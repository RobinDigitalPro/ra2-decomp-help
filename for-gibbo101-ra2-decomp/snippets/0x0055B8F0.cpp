// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0055B8F0 (432 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x13c360 (VA 0x0053C360, 432 bytes incl. padding)
// RA2 symbol : ?LogicClass_AI_Logic_507470@@YIXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/logic.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Performs the per object thinking for one game logic frame.
/// This routine gives every object that has been submitted to a layer -- animations,
/// lights, bullets, buildings, aircraft, infantry, units, particle systems, terrain,
/// voxel animations and waves -- its chance to act. It is the companion to
/// LogicClass::AI, which handles the trigger and scenario side of the same frame.
/// </summary>
void LogicClass_AI_Logic_507470(void)
{
	int index;
	for (index = Anims.Count() - 1; index >= 0; index--) {
		AnimClass * anim = Anims[index];
		if (anim->IsSubmittedToLayer) anim->AI();
	}

	for (index = BuildingLights.Count() - 1; index >= 0; index--) {
		BuildingLightClass * blight = BuildingLights[index];
		if (blight->IsSubmittedToLayer) blight->AI();
	}

	for (index = Bullets.Count() - 1; index >= 0; index--) {
		BulletClass * bullet = Bullets[index];
		if (bullet->IsSubmittedToLayer) bullet->AI();
	}

	for (index = Buildings.Count() - 1; index >= 0; index--) {
		BuildingClass * building = Buildings[index];
		if (building->IsSubmittedToLayer) building->AI();
	}

	for (index = Aircraft.Count() - 1; index >= 0; index--) {
		AircraftClass * aircraft = Aircraft[index];
		if (aircraft->IsSubmittedToLayer) aircraft->AI();
	}

	for (index = Infantry.Count() - 1; index >= 0; index--) {
		InfantryClass * infantry = Infantry[index];
		if (infantry->IsSubmittedToLayer) infantry->AI();
	}

	for (index = Units.Count() - 1; index >= 0; index--) {
		UnitClass * unit = Units[index];
		if (unit->IsSubmittedToLayer) unit->AI();
	}

	for (index = ParticleSystems.Count() - 1; index >= 0; index--) {
		ParticleSystemClass * partsys = ParticleSystems[index];
		if (partsys->IsSubmittedToLayer) partsys->AI();
	}

	for (index = Terrains.Count() - 1; index >= 0; index--) {
		TerrainClass * terrain = Terrains[index];
		if (terrain->IsSubmittedToLayer) terrain->AI();
	}

	for (index = VoxelAnims.Count() - 1; index >= 0; index--) {
		VoxelAnimClass * voxelanim = VoxelAnims[index];
		if (voxelanim->IsSubmittedToLayer) voxelanim->AI();
	}

	for (index = Waves.Count() - 1; index >= 0; index--) {
		WaveClass * wave = Waves[index];
		if (wave->IsSubmittedToLayer) wave->AI();
	}
}
