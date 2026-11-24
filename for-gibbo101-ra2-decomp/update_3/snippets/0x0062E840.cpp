// ra2-decomp help snippet, update 2026-11-23 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0062E840 (1277 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0x203250 (VA 0x00603250, 1277 bytes without padding)
// RA2 symbol : ?Spark_AI@ParticleSystemClass@@AAEXXZ
// similarity : 0.8710 (similar, masked instruction tokens; shape 1.0000)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/partsys.cpp
// License    : GPL-3.0-or-later. Our source is GPL and contains EA GPL code (section 7 terms)
//              and code adapted from mischa85/RedAlert2 and gibbo101/ra2-decomp; their
//              credits are kept. The notice of the source file follows. See ../README.md.
// Use        : a read-only lead. RA2 layouts and names; port it and match it on your own checker.

/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

/// <summary>
/// Handles the per-frame logic for a spark particle system.
/// While the system has spark frames left it throws out bursts of particles, each flung
/// along a randomly perturbed direction, either the type's spawn direction or one picked at
/// random for the burst. A light is cast on the first spark frame, and the spark radius
/// wanders from frame to frame so the shower appears to flicker. The system retires once the
/// spark frames run out.
/// </summary>
void ParticleSystemClass::Spark_AI(void)
{
	int index; // RA2: the loop counter is declared first
	if (SparkSpawnFrames > 0) {

		if (SparkSpawnFrames == 1 || Random_Double(0.0, 1.0) <= Class->SpawnSparkPercentage) {

			int random = Scen->RandomNumber();
			int count = Class->ParticleCap / 2 + abs(random) % (Class->ParticleCap / 2);

			ParticleTypeClass * held = ParticleTypes[Class->HoldsWhat];

			Random2Class & generator = Scen->RandomNumber; // RA2: the generator kept by reference
			int rand_y = generator; // RA2: as above
			int rand_x = Scen->RandomNumber(); // RA2: as above

			Vector3 spark;
			float vertical_velocity = (float)(int(generator) % held->ZVelocityRange); // RA2: as above
			spark.X = (float)(rand_x % held->XVelocity); // RA2: as above
			spark.Y = (float)(rand_y % held->YVelocity); // RA2: as above
			spark.Z = vertical_velocity; // RA2: as above

			while (count > 0) {
				ParticleClass * particle = Spawn_Held_Particle(PositionCoord, PositionCoord);

				ParticleTypeClass const * ptype = particle->Class;
				Vector3 & dir = particle->MovementDirection;

				particle->MovementDirection.X = (float)(int(Scen->RandomNumber) % ptype->XVelocity);
				particle->MovementDirection.Y = (float)(int(Scen->RandomNumber) % ptype->YVelocity);
				particle->MovementDirection.Z = (float)(ptype->MinZVelocity + abs(int(Scen->RandomNumber)) % ptype->ZVelocityRange);

				float speed = (float)dir.Length();
				if (IsRandomSparkDirection) {
					particle->MovementDirection = spark + particle->MovementDirection;
				} else {
					Vector3 & spawndir = (Vector3 &)Class->SpawnDirection;
					particle->MovementDirection = spawndir + dir; // RA2: the direction reference is used
				}
				particle->MovementDirection = Normalize_Direction(particle->MovementDirection); // RA2: the local inline normalizer
				particle->MovementDirection = speed * particle->MovementDirection;

				count--;
			}

			if (Options.DetailLevel == 2) {
				if (SparkSpawnFrames == Class->SparkSpawnFrames && Class->LightSize > 0 && !Class->OneFrameLight) {
					new SpotLightClass(PositionCoord, Class->LightSize);
				}
			}
		}

		SparkSpawnFrames--;
		if (SparkSpawnFrames <= 0) {
			IsMarkedForDeletion = true;
		}

		double chance = Random_Double(0.0, 1.0);
		if (chance < 0.3) {
			int radius; // RA2: as above
			if (SparkRadius - 3 <= 17) { // RA2: the clamp tested on the expression
				radius = 17;
			} else {
				radius = SparkRadius - 3; // RA2: as above
			}
			SparkRadius = radius;
		} else if (chance < 0.6) {
			int radius = SparkRadius + 3;
			if (radius >= 41) {
				radius = 41;
			}
			SparkRadius = radius;
		}
	}

	for (index = 0; index < SystemParticles.Count(); index++) { // RA2: as above
		SystemParticles[index]->Behavior_AI(); // RA2: as above
	}

	for (index = SystemParticles.Count() - 1; index >= 0; index--) { // RA2: as above
		ParticleClass * particle = SystemParticles[index]; // RA2: as above
		if (particle->IsToDie) {
			particle->Delete_Me();
		}
	}
}
