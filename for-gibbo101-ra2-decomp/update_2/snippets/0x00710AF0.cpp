// ra2-decomp help snippet, update 2 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00710AF0 (3406 bytes; gibbo101/ra2-decomp name: TechnoTypeClass::TechnoTypeClass)
// RA2 address: RVA 0x2cf0b0 (VA 0x006CF0B0, 2961 bytes without padding)
// RA2 symbol : ??0TechnoTypeClass@@QAE@PBDW4SpeedType@@@Z
// similarity : 0.2642 (weak, masked instruction tokens; shape 0.6491)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/techtype.cpp
// License    : GPL-3.0-or-later. Our source is GPL and contains EA GPL code (section 7 terms)
//              and code adapted from mischa85/RedAlert2 and gibbo101/ra2-decomp; their
//              credits are kept. The notice of the source file follows. See ../README.md.
// Use        : a read-only lead. RA2 layouts and names; port it and match it on your own checker.

/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2025 Electronic Arts Inc.
 * Copyright 2026 OpenTS contributors
 *
 * Contains material derived from Electronic Arts source code.
 * Modified by OpenTS contributors, 2026.
 * EA's GPLv3 Section 7 additional terms and supplemental warranty
 * disclaimers apply; see LICENSE.md.
 ******************************************************************************/

/***********************************************************************************************
 * TechnoTypeClass::TechnoTypeClass -- Constructor for techno type objects.                    *
 *                                                                                             *
 *    This is the normal constructor for techno type objects. It is called in the process of   *
 *    constructing all the object type (constant) data for the various techno type objects.    *
 *                                                                                             *
 * INPUT:   see below...                                                                       *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   03/19/1995 JLB : Created.                                                                 *
 *   05/11/1996 JLB : Moderated risk calc so range doesn't dominate.                           *
 *=============================================================================================*/
// RA2: the constructor of the types read from the rules, meastes' body at 0x6D9B40 (every member in its initialization list order)
TechnoTypeClass::TechnoTypeClass(char const * ininame, SpeedType speed) : // RA2: as above
	BASECLASS(ininame), // RA2: as above
	WalkRate(1), // RA2: as above
	IdleRate(0), // RA2: as above
	SpecialThreatValue(0.0), // RA2: as above
	MyEffectivenessCoefficient(0.0), // RA2: as above
	TargetEffectivenessCoefficient(0.0), // RA2: as above
	TargetSpecialThreatCoefficient(0.0), // RA2: as above
	TargetStrengthCoefficient(0.0), // RA2: as above
	TargetDistanceCoefficient(0.0), // RA2: as above
	ThreatAvoidanceCoefficient(0.0), // RA2: as above
	SlowdownDistance(500), // RA2: as above
	DeaccelerationFactor(0.002), // RA2: as above
	AccelerationFactor(0.03), // RA2: as above
	CloakingSpeed(7), // RA2: as above
	Locomotor(CLSID_TeleportLocomotion), // RA2: as above
	VoxelCenterY(0.0), // RA2: as above
	VoxelCenterX(0.0), // RA2: as above
	Weight(1.0), // RA2: as above
	PhysicalSize(2.0), // RA2: as above
	Size(1.0), // RA2: as above
	SizeLimit(0.0), // RA2: as above
	HoverAttack(false), // RA2: as above
	VHPScan(0), // RA2: as above
	InitialMission(MISSION_HUNT), // RA2: as above
	RollAngle(0.5235987755982988), // RA2: as above
	PitchSpeed(0.25), // RA2: as above
	PitchAngle(0.3490658503988659), // RA2: as above
	BuildLimit(0x7FFFFFFF), // RA2: as above
	Category(CATEGORY_NONE), // RA2: as above
	DeployTime(0.0), // RA2: as above
	FireAngle(8), // RA2: as above
	PipScale(PIPSCALE_NONE), // RA2: as above
	PipWrap(0), // RA2: as above
	DeploysInto(0), // RA2: as above
	UndeploysInto(0), // RA2: as above
	AuxSound1(VOC_NONE), // RA2: as above
	AuxSound2(VOC_NONE), // RA2: as above
	CreateSound(-1), // RA2: as above
	DamageSound(-1), // RA2: as above
	ImpactWaterSound(-1), // RA2: as above
	ImpactLandSound(-1), // RA2: as above
	CrashingSound(-1), // RA2: as above
	SinkingSound(-1), // RA2: as above
	VoiceFalling(-1), // RA2: as above
	VoiceCrashing(-1), // RA2: as above
	VoiceSinking(-1), // RA2: as above
	VoiceEnter(-1), // RA2: as above
	VoiceCapture(-1), // RA2: as above
	TurretRotateSound(-1), // RA2: as above
	EnterTransportSound(-1), // RA2: as above
	LeaveTransportSound(-1), // RA2: as above
	DeploySound(-1), // RA2: as above
	UndeploySound(-1), // RA2: as above
	ChronoInSound(-1), // RA2: as above
	ChronoOutSound(-1), // RA2: as above
	MZone(MZONE_NORMAL), // RA2: as above
	ThreatRange(0), // RA2: as above
	MaxDebris(0), // RA2: as above
	MinDebris(0), // RA2: as above
	MaxPassengers(0), // RA2: as above
	SightRange(0), // RA2: as above
	RevealToAll(false), // RA2: as above
	SensorsSight(0), // RA2: as above
	DetectDisguiseRange(0), // RA2: as above
	BombSight(0), // RA2: as above
	LeadershipRating(5), // RA2: as above
	NavalTargeting(0), // RA2: as above
	LandTargeting(0), // RA2: as above
	Cost(0), // RA2: as above
	Soylent(0), // RA2: as above
	FlightLevel(-1), // RA2: as above
	Level(255), // RA2: as above
	Risk(0), // RA2: as above
	Reward(0), // RA2: as above
	MaxSpeed(MPH_IMMOBILE), // RA2: as above
	Speed(speed), // RA2: as above
	InitialAmmo(-1), // RA2: as above
	MaxAmmo(-1), // RA2: as above
	IFVMode(0), // RA2: as above
	AirRangeBonus(0), // RA2: as above
	Reload(0), // RA2: as above
	EmptyReload(-1), // RA2: as above
	ReloadIncrement(0), // RA2: as above
	RadialFireSegments(0), // RA2: as above
	DeployFireWeapon(1), // RA2: as above
	DeployFire(false), // RA2: as above
	MobileFire(true), // RA2: as above
	OpportunityFire(false), // RA2: as above
	DistributedFire(false), // RA2: as above
	DamageReducesReadiness(false), // RA2: as above
	ReadinessReductionMultiplier(0.0f), // RA2: as above
	UnloadingClass(0), // RA2: as above
	AttackFriendlies(false), // RA2: as above
	AttackCursorOnFriendlies(false), // RA2: as above
	UndeployDelay(-1), // RA2: as above
	PreventAttackMove(false), // RA2: as above
	Ownable(0), // RA2: as above
	AIBasePlanningSide(-1), // RA2: as above
	StupidHunt(false), // RA2: as above
	IsAllowedToStartInMultiplayer(true), // RA2: as above
	CameoFilename(""), // RA2: as above
	CameoData(0), // RA2: as above
	CameoAllocated(false), // RA2: as above
	AltCameoFilename(""), // RA2: as above
	AltCameoData(0), // RA2: as above
	AltCameoAllocated(false), // RA2: as above
	Rotation(0), // RA2: as above
	ROT(0), // RA2: as above
	TurretOffset(0), // RA2: as above
	Points(0), // RA2: as above
	NaturalParticleSystem(0), // RA2: as above
	NaturalParticleLocation(0, 0, 0), // RA2: as above
	DamageSmokeOffset(0, 0, 0), // RA2: as above
	DamSmkOffScrnRel(false), // RA2: as above
	DestroySmokeOffset(0, 0, 0), // RA2: as above
	RefinerySmokeOffsetOne(0, 0, 0), // RA2: as above
	RefinerySmokeOffsetTwo(0, 0, 0), // RA2: as above
	ShadowIndex(0), // RA2: as above
	Capacity(0), // RA2: as above
	TurretNotExportedOnGround(false), // RA2: as above
	Gunner(false), // RA2: as above
	HasTurretTooltips(false), // RA2: as above
	TurretCount(0), // RA2: as above
	IsChargeTurret(false), // RA2: as above
	ClearAllWeapons(false), // RA2: as above
	IsTypeImmune(false), // RA2: as above
	IsMoveToShroud(true), // RA2: as above
	IsTrainable(true), // RA2: as above
	IsDamageSparks(false), // RA2: as above
	IsTargetLaser(false), // RA2: as above
	IsImmuneToVeins(false), // RA2: as above
	IsTiberiumHeal(false), // RA2: as above
	IsCloakStop(false), // RA2: as above
	IsTrain(false), // RA2: as above
	IsDropship(false), // RA2: as above
	IsToProtect(false), // RA2: as above
	IsDisableable(true), // RA2: as above
	IsUnbuildable(false), // RA2: as above
	IsDoubleOwned(false), // RA2: as above
	IsInvisible(false), // RA2: as above
	IsRadarVisible(false), // RA2: as above
	IsLeader(false), // RA2: as above
	IsScanner(false), // RA2: as above
	IsNominal(false), // RA2: as above
	IsTurretEquipped(false), // RA2: as above
	TurretRecoil(true), // RA2: as above
	TurretAnimData(2, 1, 1, 1), // RA2: +0xAB0 is built with travel 2, compress 1, recover 1, hold 1 (the same values as the NoInit constructor)
	BarrelAnimData(2, 1, 1, 1), // RA2: +0xAC4 as above
	IsRepairable(true), // RA2: as above
	IsCrew(false), // RA2: as above
	Naval(false), // RA2: as above
	IsRemappable(false), // RA2: as above
	IsCloakable(false), // RA2: as above
	GapGenerator(false), // RA2: as above
	GapRadiusInCells(0), // RA2: as above
	SuperGapRadiusInCells(0), // RA2: as above
	Teleporter(false), // RA2: as above
	IsSelfHealing(false), // RA2: as above
	IsExploding(false), // RA2: as above
	DeathWeapon(0), // RA2: as above
	DeathWeaponDamageModifier(1.0f), // RA2: as above
	IsNoAutoFire(false), // RA2: as above
	TurretSpins(false), // RA2: as above
	Normalized(false), // RA2: as above
	IsManualReload(false), // RA2: as above
	IsVisibleLoad(false), // RA2: as above
	IsLightningRod(false), // RA2: as above
	IsHunterSeeker(false), // RA2: as above
	IsCrusher(false), // RA2: as above
	IsTiltsWhenCrushes(true), // RA2: as above
	IsSubterranean(false), // RA2: as above
	IsAutoCrush(false), // RA2: as above
	CanDisguise(false), // RA2: as above
	PermaDisguise(false), // RA2: as above
	DetectDisguise(false), // RA2: as above
	DisguiseWhenStill(false), // RA2: as above
	CanApproachTarget(true), // RA2: as above
	CanRecalcApproachTarget(true), // RA2: as above
	ImmuneToRadiation(false), // RA2: as above
	DefaultToGuardArea(false), // RA2: as above
	Warpable(true), // RA2: as above
	ReselectIfLimboed(false), // RA2: as above
	RejoinTeamIfLimboed(false), // RA2: as above
	Spawned(false), // RA2: as above
	Spawns(0), // RA2: as above
	SpawnsNumber(0), // RA2: as above
	SpawnRegenRate(0), // RA2: as above
	SpawnReloadRate(0), // RA2: as above
	MissileSpawn(false), // RA2: as above
	Underwater(false), // RA2: as above
	BalloonHover(false), // RA2: as above
	SuppressionThreshold(0), // RA2: as above
	JumpjetTurnRate(4), // RA2: as above
	JumpjetSpeed(14), // RA2: as above
	JumpjetClimb(5.0f), // RA2: as above
	JumpjetCrash(5.0f), // RA2: as above
	JumpjetHeight(500), // RA2: as above
	JumpjetAccel(2.0f), // RA2: as above
	JumpjetWobbles(0.15f), // RA2: as above
	JumpjetNoWobbles(false), // RA2: as above
	JumpjetDeviation(40), // RA2: as above
	JumpJet(false), // RA2: as above
	Crashable(false), // RA2: as above
	NoShadow(false), // RA2: as above
	CanPassiveAquire(true), // RA2: as above
	CanRetaliate(true), // RA2: as above
	RequiresStolenSovietTech(false), // RA2: as above
	RequiresStolenAlliedTech(false), // RA2: as above
	RequiredHouses(-1), // RA2: as above
	ForbiddenHouses(-1), // RA2: as above
	IsSelectableCombatant(false), // RA2: as above
	IsAccelerates(true), // RA2: as above
	DisableVoxelCache(false), // RA2: as above
	DisableShadowCache(false), // RA2: as above
	ZFudgeCliff(10), // RA2: as above
	ZFudgeColumn(5), // RA2: as above
	ZFudgeTunnel(10), // RA2: as above
	ZFudgeBridge(0), // RA2: as above
	Palette(0) // RA2: as above
{
	PaletteFile[0] = '\0'; // RA2: as above
	IsSentient = true; // RA2: as above
	DebrisTypes.Clear(); // RA2: as above
	DebrisAnims.Clear(); // RA2: as above
	DebrisMaximums.Clear(); // RA2: as above
	Dock.Clear(); // RA2: as above
	int index; // RA2: as above
	for (index = 0; index < 15; index++) { // RA2: as above
		Weapons[index].Weapon = 0; // RA2: as above
		Weapons[index].BarrelLength = 0; // RA2: as above
		Weapons[index].BarrelThickness = 0; // RA2: as above
		Weapons[index].FireFLH = TPoint3D<int>(0, 0, 0); // RA2: as above
		Weapons[index].TurretLocked = false; // RA2: as above
	}
	for (index = 0; index < 15; index++) { // RA2: as above
		EliteWeapons[index].Weapon = 0; // RA2: as above
		EliteWeapons[index].BarrelLength = 0; // RA2: as above
		EliteWeapons[index].BarrelThickness = 0; // RA2: as above
		EliteWeapons[index].FireFLH = TPoint3D<int>(0, 0, 0); // RA2: as above
		EliteWeapons[index].TurretLocked = false; // RA2: as above
	}
	for (index = 0; index < 15; index++) { // RA2: as above
		TurretWeapon[index] = -1; // RA2: as above
	}
	AbstractTypePtrTracker.Add(this); // RA2: as above
	TechnoTypes.Add(this); // RA2: as above
}

// ---- companion (struct TechnoUnused2, from src/m85/include/techtype.h): the function above depends on it ----
struct TechnoUnused2
{
	TechnoUnused2(void) : Value(0) {}

	int Value;
};
