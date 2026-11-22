# Fixes to mischa85/RedAlert2 that are not specific to 1.001

The base is mischa85 commit `0132d217` (the files we adopted), diffed against our `src/m85` (2026-11-22). Path-literal and geoconst-include changes are normalised away.

"1.006 copy" means `RA2SteamVersion/game.exe`, SHA-256 `a48035e0...`. It is the same build as their target, but its hash differs (see README). Every 1.006 statement below is therefore a lead to confirm with objdiff on their hash-verified exe.

## Classification of our changes

Units: distinct functions or file scopes in their source that our diff touches. The function is located by its enclosing definition in their file, so the counts are approximate.

| Category | Count | How it was decided |
|---|---|---|
| (a1) plain mistakes, checked by hand | 14 corrections in entries 1-10 and 12, plus 3 RTTI observations (entry 11) | The string, table or RTTI name is absent from both binaries in their form and present in both in ours; or a declared-but-undefined function |
| (a2) source corrections confirmed by 1.006 bytes | 99-101 functions, about 201 KB | We changed the function. Our compiled bytes occur exactly once in the 1.006 copy, at an address their `names.csv` does not mark as matched |
| (b) 1.001-specific | 373 functions | 352: their form is already matched on 1.006 per their `names.csv`, so our change is a 1.001 difference. 21: our 1.001 bytes do not occur in the 1.006 copy |
| (c) uncertain | 244 functions | Not (yet) matched on 1.001, or several hits in 1.006 |
| file scope | 52 places | includes, declarations, tables outside functions; reviewed only for strings (a1) |

Also not counted as fixes:
- 38 files that differ only by the `C:\RA2\` path literal or the geoconst includes;
- 35 files we added (see `missing.md`).

String evidence: the literal was looked up as NUL-terminated data in both binaries (wide for `L"..."`):

| String, their form | In 1.001 | In 1.006 copy | String, our form | In 1.001 | In 1.006 copy |
|---|---|---|---|---|---|
| `SUN.INI` | no | no | `RA2.INI` | yes | yes |
| `L""` (Full_Name) | – | – | `L"No name"` | yes | yes |
| `IonCannon`, `ChemMissile` | no | no | `IronCurtain` ... `AmerParaDrop` | yes | yes |
| `Struggle` | no | no | `Tread` ... `Panic` (18 names) | yes | yes |
| `TS Sync\n` | no | no | `RA2 Sync\n` | yes | yes |
| `CPU %01d86, MMX %s, Vendor: %s\r\n` | no | no | `CPU %s, MMX %s, Vendor: %s\r\n` | yes | yes |
| `b350c6d2-2f36-11d3-a72c-0090272fa661` | no | no | `01AF9993-3492-11d3-8F6F-0060089C05B1` | yes | yes |
| `PlaySide%02d` | no | no | `Play` (key) | yes | yes |
| `FiringSyncFrame1`, `FiringSyncFrame2` | no | no | `FiringSyncFrame%d`, `BurstDelay%d` | yes | yes |
| `Recive buffer overflow %d\n` | no | no | `Receive buffer overflow %d\n` | yes | yes |

## (a1) Plain mistakes, with diffs

### 1. include/sun.h: CONFIG_FILE_NAME
- Evidence: 1.001 `0x7C69C4` holds `"RA2.INI"`. `RA2.INI` is in both binaries; `SUN.INI` is in neither. Their `startup.cpp` WinMain uses the macro.

```diff
-#define CONFIG_FILE_NAME		"SUN.INI"
+#define CONFIG_FILE_NAME		"RA2.INI" // RA2: the config file
```

### 2. include/object.h: ObjectClass::Full_Name
- Evidence: the default returns `L"No name"` (1.001 `0x7b9c40`). The wide string is in both binaries.

```diff
-		virtual wchar_t const * Full_Name(void) const {return(L"");} // RA2: wide
+		virtual wchar_t const * Full_Name(void) const {return(L"No name");} // RA2: wide
```

### 3. src/suprtype.cpp: Special_From_Name name table (TibSun names)
- Evidence: the data at 1.001 `0x7dfed8` is the RA2 list. `IonCannon` and `ChemMissile` exist in neither binary.
- Their code bytes can still match because the table pointers are masked.

```diff
 	static const char * _names[SUPER_COUNT] = {
 		"MultiMissile",
-		"EMPulse",
-		"Firestorm",
-		"IonCannon",
-		"HunterSeeker",
-		"ChemMissile",
-		"DropPod"
+		"IronCurtain",
+		"LightningStorm",
+		"ChronoSphere",
+		"ChronoWarp",
+		"ParaDrop",
+		"AmerParaDrop"
 	};
```

### 4. src/infatype.cpp: infantry sequence-name table (TibSun list)
- Evidence: all 18 added RA2 names are in both binaries, and `Struggle` is in neither.
- InfantryTypeClass::From_Name / Read_INI are matched on 1.006 because the table entries are masked. The data is still wrong.

```diff
 	"Die5",
+	"Tread",
+	"Swim",
+	"WetIdle1",
+	"WetIdle2",
+	"WetDie1",
+	"WetDie2",
+	"WetAttack",
 	"Hover",
 	"Fly",
 	"Tumble",
 	"FireFly",
-	"Struggle"
+	"Deploy",
+	"Deployed",
+	"DeployedFire",
+	"DeployedIdle",
+	"Undeploy",
+	"Cheer",
+	"Paradrop",
+	"AirDeathStart",
+	"AirDeathFalling",
+	"AirDeathFinish",
+	"Panic"
 };
```
- Check the sequence enum (DoType) in their header against this list: the names are indexed by it.

### 5. src/queue.cpp: Print_CRCs file header and CPU line
- Evidence: the strings, as in the table above.
- `Get_CPU_Type_Name()` is their own RA2 function (`getcpu.cpp`, 1.006 0x4D2B80). Their `except.cpp` already prints the CPU line this way.
- Our Print_CRCs as a whole differs from 1.006 in other places, so the function itself is not offered.

```diff
-	fprintf(fp, "TS Sync\n");
+	fprintf(fp, "RA2 Sync\n");
@@
-	Get_CPU_Type(cpu_type, mmx);
-	fprintf(fp, "CPU %01d86, MMX %s, Vendor: %s\r\n", cpu_type, mmx ? "Yes" : "No", &VendorID);
+	Get_CPU_Type(cpu_type, mmx, NULL, 0);
+	fprintf(fp, "CPU %s, MMX %s, Vendor: %s\r\n", Get_CPU_Type_Name(), mmx ? "Yes" : "No", &VendorID);
```

### 6. src/startup.cpp: AUTOPLAY_GUID
- Evidence: their GUID is in neither binary; ours is in both.

```diff
-#define AUTOPLAY_GUID "b350c6d2-2f36-11d3-a72c-0090272fa661"
+#define AUTOPLAY_GUID "01AF9993-3492-11d3-8F6F-0060089C05B1"
```

### 7. src/startup.cpp WinMain: the intro key
- Evidence: `PlaySide%02d` (TibSun's GDI/Nod disks) is in neither binary. 1.001 reads and writes one `[Intro] Play` key for every disk above DISK_ANY.
- Our WinMain also has 1.001-only parts (the WOLAPI options and a `Get_Performance_Profile` call), which are not part of this fix. Check the 1.006 control flow before copying more than the key.

```diff
-		if (!Special.IsFromInstall && (disk == DISK_GDI || disk == DISK_NOD)) {
-			sprintf(buffer, "PlaySide%02d", disk);
-			Special.IsFromInstall = ConfigINI.Get_Bool("Intro", buffer, true);
+		if (!Special.IsFromInstall && disk > DISK_ANY) {
+			Special.IsFromInstall = ConfigINI.Get_Bool("Intro", "Play", true);
 		}
@@
-			if ((disk == DISK_GDI || disk == DISK_NOD)) {
-				sprintf(buffer, "PlaySide%02d", disk);
-				ConfigINI.Put_Bool("Intro", buffer, false);
+			if (disk > DISK_ANY) {
+				Special.IsFromInstall = ConfigINI.Put_Bool("Intro", "Play", false);
 			}
```

### 8. src/unittype.cpp UnitTypeClass::Read_INI: numbered sync frames and burst delays
- Evidence: `FiringSyncFrame1`/`2` are in neither binary; the `%d` format strings are in both. This is a layout hint too: `BurstDelay[4]` is read here.

```diff
-		FiringSyncFrame[0] = ArtINI.Get_Int(Graphic_Name(), "FiringSyncFrame1", FiringSyncFrame[0]);
-		FiringSyncFrame[1] = ArtINI.Get_Int(Graphic_Name(), "FiringSyncFrame2", FiringSyncFrame[1]);
+		for (int i = 0; i < 2; i++) {
+			char buffer[20];
+			sprintf(buffer, "FiringSyncFrame%d", i);
+			FiringSyncFrame[i] = ArtINI.Get_Int(Graphic_Name(), buffer, FiringSyncFrame[i]);
+		}
+
+		for (int j = 0; j < 4; j++) {
+			char buffer[20];
+			sprintf(buffer, "BurstDelay%d", j);
+			BurstDelay[j] = ini.Get_Int(Name(), buffer, BurstDelay[j]);
+		}
```
- Note that the key index starts at 0 (`FiringSyncFrame0`), as the 1.001 code builds it.

### 9. src/ipxmgr.cpp IPXManagerClass::Service: overflow message
- Evidence: `Recive buffer overflow %d\n` is in neither binary.
- Both binaries hold `Receive buffer overflow %d\n`, `RouterChannel recive buffer overflow %d\n` and `Reecive buffer overflow %d\n`. The 1.001 Service has three overflow branches; the third string's caller in 1.006 still has to be found.

```diff
-								DebugString("Recive buffer overflow %d\n", ReceiveOverflows);
+								DebugString("Receive buffer overflow %d\n", ReceiveOverflows);
```

### 10. RTTI-proven names (src/building.cpp, src/smartdeform.cpp, include/spawnmgr.h)
- Evidence: the RTTI type descriptors in both binaries are:
  - `.?AV?$DynamicVectorClass@PAVReestablish@@@@`
  - `.?AV?$DynamicVectorClass@UUndoInfoStruct@@@@`
  - `.?AV?$DynamicVectorClass@PAUSpawnControl@@@@`
- Their `names.csv` uses `DeformUndoStruct` (9 symbols, e.g. 0x686F70 `?ID@?$DynamicVectorClass@UDeformUndoStruct@@@@...`) and `SpawnControl@SpawnManagerClass` (0x68B0E0, 0x7AB92C, 0x7AB94C). These decorations do not exist in the game.

```diff
-struct ReestablishRecord { // RA2: the 8-byte record Captured allocates per captured contact
+class Reestablish { // RA2: RTTI .?AV?$DynamicVectorClass@PAVReestablish@@@@
+public:
 	TechnoClass * Contact;
 	bool WasTethered;
-	ReestablishRecord(TechnoClass * contact, bool tethered) : Contact(contact), WasTethered(tethered) {}
+	Reestablish(TechnoClass * contact, bool tethered) : Contact(contact), WasTethered(tethered) {}
 };
```
```diff
-struct DeformUndoStruct {
+struct UndoInfoStruct { // RA2: RTTI .?AV?$DynamicVectorClass@UUndoInfoStruct@@@@
 (and every DeformUndoStruct inside the struct and its uses)
```
```diff
+struct SpawnControl   // RA2: a global struct, RTTI .?AV?$DynamicVectorClass@PAUSpawnControl@@@@
+{
+	AircraftClass * Unit;
+	int Status;
+	CDTimerClass<FrameTimerClass> SpawnTimer;
+	BOOL IsSpawnMissile;
+};
+
 class SpawnManagerClass : public AbstractClass
 {
 	...
-		struct SpawnControl
-		{
-			...
-		};
```

### 11. RTTI observations we have NOT changed in our tree either (for completeness)
Their `names.csv` vtable symbols that disagree with the RTTI strings in both binaries:

| Their vtable symbol | RTTI in the game |
|---|---|
| 0x7A53B4 `??_7?$DynamicVectorClass@PAVKamikazeControl@@@@6B@`, 0x7A53D4 (VectorClass) | `.?AV?$DynamicVectorClass@PAUKamikazeControl@@@@`: a **struct** |
| 0x7A549C `??_7LoadProgressManager@@6B@` | `.?AVLoadProgressMgr@@`: the class name is **LoadProgressMgr** |
| 0x7AF1FC / 0x7AF25C `...PAVAnimationPalette@Map@WorldDominationTour@@...` | `...PAUAnimationPalette@Map@WorldDominationTour@@...`: a **struct** |

The other 516 `??_7` symbols in their `names.csv` agree with the RTTI strings.

### 12. src/planmgr.cpp: Planning_Adjusted_Pixel declared but not defined
- `planning.h` declares it, and their `names.csv` names it at 0x619E00, but no definition exists in their tree.
- Our definition matches 1.001 `0x2119e0`, and its bytes occur exactly once in the 1.006 copy, at 0x619E00.

```diff
+#pragma auto_inline(off)
+int __fastcall Planning_Adjusted_Pixel(RGBClass const & rgb, RGBClass const & target, int ratio) // RA2: 0x00619E00
+{
+	RGBClass color = rgb;
+	color.Adjust(ratio, target);
+	return ((color.Get_Red() >> DSurface::RedLeft) << DSurface::RedRight) | ((color.Get_Green() >> DSurface::GreenLeft) << DSurface::GreenRight) | ((color.Get_Blue() >> DSurface::BlueLeft) << DSurface::BlueRight);
+}
+#pragma auto_inline(on)
```

### Not counted as fixes, though they look like it
- **cdcntrl.cpp `"%c:\\"` -> `".\\"`:** this is our repack's no-CD change.
- **ownrdraw `guparrow%c.pcx` -> `uparrow%c.pcx` and wonline `gt18.pcx` -> `gt18.bmp`:** both forms are in the 1.006 copy, so both may be used there.
- **Many debug strings that are absent in 1.001** (`... - error code %d.`, `%d/%d with %d seconds left`): these are 1.006 additions.

## (a2) Source corrections whose compiled bytes also occur once in the 1.006 copy

We changed these functions relative to their source, and the result matches 1.001 byte-identically. With our relocation fields masked, the same bytes occur **exactly once** in the 1.006 copy, at the address in the table. Their `names.csv` does not mark that address as matched:
- "named" means they have only an inferred name there;
- "unnamed" means no name;
- "function start known" means their `functions.csv` has that start.

So their source for these functions is not 1.006-exact, and our form probably is.

**Typical causes**, all general VC6 effects (see `vc6_rules.md`):
- hand-flattened inline helpers restored to calls: `delta.Length()`, `_Scale_To_256`, `Free_Image`, cast helpers, cell-data accessors in mapgen;
- m85's own `static inline` helpers dissolved into the caller;
- explicit `!= 0` / `== NULL` in **header** inlines made implicit. One token in `findmake.h` `TGet_Class` made RulesClass::General (14 KB) match;
- typed INI locals;
- block scopes and stack-slot layout;
- `List.ID(x) == -1` replaced by `!List.Is_In_List(x)`.

**Caveats:**
- The bytes depend on our headers as well as the `.cpp`. Port the function together with the header forms it uses, and verify with objdiff.
- The full per-function diff is large (about 350 KB). It can be regenerated with `git diff --no-index <their 0132d21 src/x.cpp> <our src/m85/src/x.cpp>`, or provided on request.
- The 1.006 addresses come from the unverified copy.

| Function | Our file | 1.001 RVA | 1.006 VA (copy) | Bytes | m85 row at that VA |
|---|---|---|---|---|---|
| RulesClass::General | rules.cpp | 0x23eff0 | 0x647f40 | 14160 | named (function start known) |
| TechnoTypeClass::Read_INI | techtype.cpp | 0x2d04d0 | 0x6daf60 | 12672 | named (function start known) |
| RulesClass::Audio_Visual_Rules | rules.cpp | 0x23aec0 | 0x643e10 | 11168 | named (function start known) |
| DriveLocomotionClass::Start_Of_Move | drive.cpp | 0xa2390 | 0x4a2670 | 8384 | named (function start known) |
| ShipLocomotionClass::Start_Of_Move | ship.cpp | 0x26df40 | 0x6785c0 | 8384 | named (function start known) |
| ScoreClass::Presentation | score.cpp | 0x25af90 | 0x663fe0 | 7792 | unnamed |
| RulesClass::RulesClass | rules.cpp | 0x237c30 | 0x640b80 | 7776 | unnamed |
| TechnoClass::Take_Damage | techno.cpp | 0x2c31b0 | 0x6cdc40 | 4432 | named (function start known) |
| UnitClass::Do_MISSION_UNLOAD | unit.cpp | 0x2f6200 | 0x701580 | 4128 | unnamed |
| Put_All | saveload.cpp | 0x24c950 | 0x6558b0 | 4064 | unnamed |
| UnitClass::Unit_Draw_Voxel | unit.cpp | 0x2f4310 | 0x6ff690 | 3872 | unnamed |
| RulesClass::Combat_Damage | rules.cpp | 0x23dd10 | 0x646c60 | 3840 | named (function start known) |
| Get_All | saveload.cpp | 0x24dc10 | 0x656b80 | 3808 | named (function start known) |
| FlyLocomotionClass::Movement_AI | fly.cpp | 0xbc9c0 | 0x4bcd50 | 3792 | named (function start known) |
| AnimClass::AI | anim.cpp | 0x21710 | 0x421710 | 3632 | unnamed |
| Map::Load | wdtmap.cpp | 0x31e0d0 | 0x729510 | 3440 | unnamed |
| UnitClass::Per_Cell_Process | unit.cpp | 0x2f3290 | 0x6fe610 | 3392 | unnamed |
| TechnoClass::Draw_Post_Render | techno.cpp | 0x2b82b0 | 0x6c2c40 | 3344 | unnamed |
| BuildingClass::Do_MISSION_DECONSTRUCTION | building.cpp | 0x45890 | 0x445b30 | 3312 | unnamed |
| TechnoClass::Evaluate_Object | techno.cpp | 0x2baba0 | 0x6c5570 | 3008 | named (function start known) |
| BulletClass::Detonate | bullet.cpp | 0x61d40 | 0x462110 | 2880 | named (function start known) |
| DisplayClass::Mouse_Left_Up | display.cpp | 0x9aed0 | 0x49b0f0 | 2608 | named (function start known) |
| BuildingClass::Take_Damage | building.cpp | 0x3ec00 | 0x43ee70 | 2512 | unnamed |
| MapGeneratorClass::Spread_Land | mapgen.cpp | 0x17a1a0 | 0x57d3a0 | 2416 | named (function start known) |
| BuildingClass::Do_Destruction | building.cpp | 0x3e000 | 0x43e270 | 2352 | unnamed |
| UnitClass::Unit_Draw_Shape | unit.cpp | 0x2f5230 | 0x7005b0 | 2240 | unnamed |
| InfantryClass::Assign_Destination | infantry.cpp | 0x1011a0 | 0x501ce0 | 1936 | unnamed |
| LaserDrawClass::Draw_It | laser.cpp | 0x131750 | 0x5334f0 | 1920 | named (function start known) |
| FlyLocomotionClass::Process_Landing | fly.cpp | 0xbdc20 | 0x4bdfb0 | 1904 | named (function start known) |
| ParticleSystemClass::Railgun_AI | partsys.cpp | 0x203c30 | 0x60c050 | 1904 | named (function start known) |
| InfantryClass::Tunnel_AI | infantry.cpp | 0x101a80 | 0x5025c0 | 1888 | named (function start known) |
| BuildingLightClass::AI | blight.cpp | 0x33830 | 0x433970 | 1824 | unnamed |
| LogicClass::AI | logic.cpp | 0x13ba70 | 0x53d890 | 1824 | named (function start known) |
| HoverLocomotionClass::Start_Of_Move | hover.cpp | 0xfd5f0 | 0x4fe0f0 | 1808 | named (function start known) |
| WaveClass::Draw_Sonic | wave.cpp | 0x317170 | 0x7225b0 | 1792 | named (function start known) |
| AnimClass::Flaming_Guy_AI | anim.cpp | 0x23120 | 0x423120 | 1680 | unnamed |
| Read_PCX_File | pcx.cpp | 0x204cf0 | 0x60d110 | 1648 | named (function start known) |
| TechnoClass::Get_Z_Adjust | techno.cpp | 0x2c5410 | 0x6cfea0 | 1648 | named (function start known) |
| ParticleClass::Gas_Behavior_AI | particle.cpp | 0x200790 | 0x608bb0 | 1616 | named (function start known) |
| UnitClass::Scatter | unit.cpp | 0x2fbee0 | 0x7072d0 | 1568 | unnamed |
| TechnoClass::Draw_Shaded_Line | techno.cpp | 0x2c6330 | 0x6d0dc0 | 1520 | unnamed |
| BulletClass::Unlimbo | bullet.cpp | 0x612e0 | 0x4616b0 | 1344 | unnamed |
| MapRegionClass::Build_Corner_Ramp_SE | mapgen.cpp | 0x1711e0 | 0x5743f0 | 1344 | unnamed |
| MapGeneratorClass::Generate_Rural_Roads | mapgen.cpp | 0x186fb0 | 0x58a1b0 | 1328 | named (function start known) |
| TeamTypeClass::Suggested_New_Team | teamtype.cpp | 0x2b43a0 | 0x6bed50 | 1296 | named (function start known) |
| Tactical::Pixel_To_Cell | tactical.cpp | 0x29c210 | 0x6a6bd0 | 1280 | named (function start known) |
| TechnoClass::Draw_Voxel | techno.cpp | 0x2c7270 | 0x6d1d00 | 1248 | named (function start known) |
| _Graphic_Menu | grphmenu.cpp | 0xdda10 | 0x4de380 | 1184 | named (function start known) |
| TeamClass::Calc_Center | team.cpp | 0x2aec60 | 0x6b9610 | 1168 | named (function start known) |
| TechnoClass::Draw_Action_Line | techno.cpp | 0x2c5a80 | 0x6d0510 | 1152 | named (function start known) |
| AlphaShapeClass::Draw_In_Area | alphashp.cpp | 0x1f1c0 | 0x41f1c0 | 1056 | named (function start known) |
| Save_Game | saveload.cpp | 0x24c540 | 0x6554a0 | 1040 | named (function start known) |
| JumpjetLocomotionClass::Process_Descent | jumpjet.cpp | 0x12e7b0 | 0x530550 | 1008 | named (function start known) |
| Generate_Starting_Points | mapgen.cpp | 0x173210 | 0x576420 | 1008 | named (function start known) |
| Selection::Pick_Territory | wdtsel.cpp | 0x322c10 | 0x72e050 | 992 | named (function start known) |
| TechnoClass::Draw_Pre_Render | techno.cpp | 0x2b91a0 | 0x6c3b30 | 976 | unnamed |
| ParticleSystemClass::Fire_AI | partsys.cpp | 0x2043a0 | 0x60c7c0 | 944 | named (function start known) |
| UnVQ2_4x4_Table | unvqtblc.cpp | 0x3003e0 | 0x70b820 | 928 | unnamed |
| Tactical::Draw_Shroud | tactical.cpp | 0x29ce60 | 0x6a7820 | 896 | named (function start known) |
| AlphaShapeClass::Draw_All | alphashp.cpp | 0x1f5e0 | 0x41f5e0 | 880 | unnamed |
| TunnelLocomotionClass::Process_Tunneling | tunnel.cpp | 0x2e59f0 | 0x6f0730 | 880 | named (function start known) |
| FlyLocomotionClass::Move_To | fly.cpp | 0xbc050 | 0x4bc3e0 | 848 | unnamed |
| AircraftClass::Read_INI | aircraft.cpp | 0x1a840 | 0x41a840 | 832 | named (function start known) |
| DisplayClass::Set_Cursor_Pos | display.cpp | 0x992b0 | 0x4994d0 | 832 | named (function start known) |
| Draw_Unit_Info | dropship.cpp | 0xa94c0 | 0x4a97b0 | 832 | unnamed |
| GraphicMenu::Presentation | grphmenu.cpp | 0xde070 | 0x4de9e0 | 832 | named (function start known) |
| InfantryClass::Start_Driver | infantry.cpp | 0x104050 | 0x504bc0 | 832 | unnamed |
| BuildingClass::Do_MISSION_GUARD | building.cpp | 0x45380 | 0x445620 | 800 | unnamed |
| BuildingClass::What_Action | building.cpp | 0x43600 | 0x4438a0 | 768 | unnamed |
| SuperClass::Discharged | super.cpp | 0x292730 | 0x69d090 | 768 | named (function start known) |
| TechnoClass::Area_Modify | techno.cpp | 0x2ba8a0 | 0x6c5270 | 768 | unnamed |
| IonBlastClass::Draw_It | ionblast.cpp | 0x121220 | 0x521ce0 | 720 | named (function start known) |
| TechnoClass::Techno_Blit_Voxel | techno.cpp | 0x2c7f40 | 0x6d29d0 | 720 | named (function start known) |
| FootClass::Safety_Point | findpath.cpp | 0xbb060 | 0x4bb3f0 | 688 | named (function start known) |
| _Create_Group | reinf.cpp | 0x231340 | 0x639da0 | 688 | unnamed |
| UnitClass::Visceroid_AI | unit.cpp | 0x2f0bd0 | 0x6fbf40 | 688 | named (function start known) |
| Tactical::Draw_Fence_Placement | tactical.cpp | 0x29b3b0 | 0x6a5d70 | 672 | named (function start known) |
| ScenarioClass::ScenarioClass | scenario.cpp | 0x252580 | 0x65b4f0 | 656 | unnamed |
| Tactical::Draw_Firestorm_Wall_Placement | tactical.cpp | 0x29b650 | 0x6a6010 | 640 | named (function start known) |
| Palette_Scheme_Count | palette.cpp | 0x1fb930 | 0x603d50 | 592 | unnamed |
| UnitClass::Rotation_AI | unit.cpp | 0x2f0520 | 0x6fb890 | 544 | named (function start known) |
| BuildingClass::Docking_Coord | building.cpp | 0x43e70 | 0x4440e0 | 464 | unnamed |
| DisplayClass::Center_Map | display.cpp | 0x9e0e0 | 0x49e3b0 | 448 | named (function start known) |
| Tactical::Flag_Cell | tactical.cpp | 0x2a0410 | 0x6aadd0 | 432 | named (function start known) |
| SurfaceCacheClass::Draw | srfcache.cpp | 0x2823e0 | 0x68cce0 | 416 | named (function start known) |
| TechnoClass::TechnoClass | techno.cpp | 0x2b7580 | 0x6c1f10 | 416 | named (function start known) |
| TActionClass::TActionClass | taction.cpp | 0x2a29c0 | 0x6ad370 | 384 | named (function start known) |
| BuildingClass::Turret_Coord | building.cpp | 0x4e8e0 | 0x44ebf0 | 368 | unnamed |
| BulletClass::BulletClass | bullet.cpp | 0x5f020 | 0x45f3b0 | 320 | unnamed |
| DisplayClass::DisplayClass | display.cpp | 0x98830 | 0x498a50 | 288 | named (function start known) |
| WideWstring::trimTrailing | wstring.cpp | 0x35bb70 | 0x770230 | 256 | named (function start known) |
| BuildingClass::Fire_Direction | building.cpp | 0x48ed0 | 0x4491e0 | 176 | unnamed |
| JumpjetLocomotionClass::JumpjetLocomotionClass | jumpjet.cpp | 0x12d3c0 | 0x52f160 | 176 | unnamed |
| VQA_Reset | vqalib_task.cpp | 0x368110 | 0x77c7d0 | 176 | named (function start known) |
| WideWstring::removeChar | wstring.cpp | 0x35ba50 | 0x770110 | 160 | named (function start known) |
| SidebarClass::Abandon_Production | sidebar.cpp | 0x276ea0 | 0x681740 | 144 | named (function start known) |
| DisplayClass::One_Time | display.cpp | 0x98950 | 0x498b70 | 112 | named (function start known) |
| WideWstring::trimLeading | wstring.cpp | 0x35bb10 | 0x7701d0 | 96 | unnamed |
| IsometricTileTypeClass::Preview_Tile | isotype.cpp | 0x12c5f0 | 0x52e390 | 64 | named (function start known) |
| PlanningFirstTarget::Get_Event_Frame | planmgr.cpp | 0x211eb0 | 0x61a2d0 | 32 | unnamed |
| SidebarClass::Zoom_Mode_Control | sidebar.cpp | 0x276fe0 | 0x6818b0 | 32 | named (function start known) |
