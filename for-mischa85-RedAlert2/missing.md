# What we have that mischa85/RedAlert2 lacks or leaves unmatched

Sources:
- Our latest full check, `check_2026-11-22T174744Z.json`: 17,527 functions byte-identical on 1.001 with verified bindings.
- Their `config/ra2-1.006` (commit 8f715e2) and `src/` (0132d21 / 8f715e2).

All 1.006 addresses come from the unverified copy (see README): treat them as leads.

## 1. Files we added to their tree (`src/m85`)

| File | 1.001 functions matched | Bytes | What it is |
|---|---|---|---|
| `src/_rules.cpp`, `_mixfile.cpp`, `_palette.cpp`, `_script.cpp`, `_astar.cpp`, `_astar2.cpp`, `_command.cpp`, `_logic.cpp`, `_map.cpp`, `_convert.cpp`, `_isotile.cpp`, `_vanim.cpp`, `_voxel.cpp`, `_weapon.cpp`, `_alpha.cpp`, `_milsectmr.cpp` | 70 | 3,616 | New TUs that DEFINE the global objects their `_xxx.h` headers only declare (for example ArtINI, UIINI and AIINI with their constructor and atexit initializers). They are placed by the 1.001 initializer order. |
| `src/combuf2.cpp` | 3 | 256 | CommandBuffer helpers and the explicit hotkey index instantiation (structure from gibbo101) |
| `src/const.cpp` | 1 | 128 | the constant-table initializer (from gibbo101) |
| `include/hashstr.h` | (header) | | HashString as a shared header (theirs is file-local in palette.cpp). In 1.001, `operator==` is non-const and `operator!=` is out of line. See also the name difference at 0x4E11F0 below. |
| `src/asm/` (13 `.asm` + 3 `.inc`) | 62 | 19,809 | MASM sources of the original's assembly objects (winasm, unvq_asm, vqa_sos, soscodec, olsosdec, auduncmp, isoasm, cliprect, detproc, cmathstuff, smartdeform_, vqa_uncomp). `repack_nocd.asm` is specific to our repack baseline. They are listed for information only: their rules ban asm fakes. |

## 2. Our own TUs without a counterpart in their `src/` (`src/ra2`)

- In total, 205 TUs hold 5,289 matched functions (310,611 bytes).
- Named TUs:
  - `MPObserver.cpp` (MultiplayerObserverTeam, 19 functions);
  - `TXTBUTTN.CPP` (8);
  - `WDTProps.cpp` (CampaignProperties and related, 21);
  - three template-instance TUs:
    - `VECTOR_INSTANCES.cpp`: 1,767 VectorClass / DynamicVectorClass / CounterClass COMDAT copies, 127 KB, each bound to its 1.001 address;
    - `FACTORY_INSTANCES.cpp`: 369 TClassFactory/COM instances, 27 KB;
    - `BLIT_INSTANCES.cpp`: 227 Blit template instances, 17 KB.
- 199 placeholder TUs `unnamed/TU_<rva>.cpp`. These are 1.001 object ranges whose file name is not known. The largest are TU_5A4120 (47 functions), TU_4D2270 (139, mostly initializers), TU_47FCC0, TU_463F40, TU_714AB0 and TU_6D9E50.
- We also have our own versions of TUs they do have, with many functions they do not name. Among them are Init, netdlg2, netshare, coopcamp, MPCoop, ModemGst/ModemHst, Skirmish, UICmnds, CampScor, NullMgr, WOLPersonaInformation, Conquer, Ion, GDlgSupp, Multiplayer, Beacon and SerialEd. See the table in section 3.

## 3. 1.001-matched functions whose decorated symbol is absent from their `names.csv`

- 4,295 functions (654,448 bytes), not counting compiler-generated `??_` and `_$E`. For 3,475 of them, not even the name with its class occurs in their `names.csv`.
- The rest differ only in signature spelling, for example `CoordStruct` versus `Coord` or `RectangleStruct` versus `TRect<int>`. Those are naming disagreements, not missing code.
- Largest TUs:

| TU | Functions | Bytes | of which name+class unknown to their names.csv |
|---|---|---|---|
| src/ra2/templates/VECTOR_INSTANCES.cpp | 1425 | 100944 | 1267 |
| src/m85/src/wonline.cpp | 166 | 88448 | 154 |
| src/m85/src/unit.cpp | 12 | 30320 | 11 |
| src/ra2/templates/FACTORY_INSTANCES.cpp | 369 | 26992 | 368 |
| src/m85/src/ownrdraw.cpp | 57 | 24864 | 52 |
| src/m85/src/building.cpp | 22 | 15936 | 21 |
| src/m85/src/mapgen.cpp | 35 | 13312 | 28 |
| src/m85/src/convert.cpp | 38 | 12320 | 38 |
| src/ra2/templates/BLIT_INSTANCES.cpp | 119 | 12067 | 89 |
| src/m85/src/startup.cpp | 79 | 11744 | 5 |
| src/m85/src/rules.cpp | 29 | 11504 | 6 |
| src/ra2/netshare.cpp | 49 | 10736 | 49 |
| src/m85/src/map.cpp | 53 | 9904 | 41 |
| src/ra2/unnamed/TU_5A4120.cpp | 43 | 9712 | 2 |
| src/ra2/netdlg2.cpp | 21 | 9568 | 20 |
| src/ra2/ModemGst.cpp | 19 | 9216 | 19 |
| src/m85/src/house.cpp | 54 | 9116 | 33 |
| src/m85/src/techno.cpp | 10 | 8992 | 10 |
| src/ra2/ModemHst.cpp | 31 | 8736 | 31 |
| src/m85/src/saveload.cpp | 36 | 8496 | 36 |
| src/ra2/MPCoop.cpp | 36 | 8464 | 35 |
| src/m85/src/score.cpp | 3 | 7904 | 2 |
| src/ra2/coopcamp.cpp | 27 | 7552 | 23 |
| src/ra2/Skirmish.cpp | 10 | 7200 | 10 |
| src/ra2/UICmnds.cpp | 59 | 6576 | 55 |
| src/ra2/CampScor.cpp | 16 | 5904 | 15 |
| src/m85/src/wdtmap.cpp | 33 | 5824 | 24 |
| src/m85/src/anim.cpp | 22 | 5712 | 22 |
| src/m85/src/palette.cpp | 33 | 5568 | 26 |
| src/ra2/Ion.cpp | 19 | 5088 | 19 |


## 4. Functions whose bytes we can place in 1.006 where they have no match (`1006_check.csv`)

- 540 functions (323,290 bytes) meet their 32-byte/60% rule and occur exactly once in the 1.006 copy at an address their `names.csv` does not mark as matched. 119 more are below the rule.

| Where | Their state at that address | Functions | Bytes |
|---|---|---|---|
| our m85-derived TUs | named (inferred) and function start known | 157 | 160,192 |
| our m85-derived TUs | no name, no known start (inside a chunk) | 164 | 111,018 |
| our m85-derived TUs | no name, start known | 86 | 32,880 |
| our src/ra2 TUs | named, start known | 12 | 1,632 |
| our src/ra2 TUs | no name, no known start | 72 | 9,024 |
| our src/ra2 TUs | no name, start known | 49 | 8,544 |

- Rows with no known start are a direct split of one of their `chunk_<address>` pieces: start and size come from our object.
- Largest TUs:

| TU | Functions | Bytes |
|---|---|---|
| src/m85/src/rules.cpp | 4 | 36944 |
| src/m85/src/mapgen.cpp | 27 | 33088 |
| src/m85/src/techno.cpp | 14 | 20752 |
| src/m85/src/unit.cpp | 9 | 19040 |
| src/m85/src/techtype.cpp | 5 | 13024 |
| src/m85/src/convert.cpp | 38 | 12320 |
| src/m85/src/builtype.cpp | 5 | 11664 |
| src/m85/src/building.cpp | 9 | 10800 |
| src/m85/src/saveload.cpp | 3 | 8912 |
| src/m85/src/planmgr.cpp | 31 | 8560 |
| src/m85/src/drive.cpp | 2 | 8416 |
| src/m85/src/ship.cpp | 1 | 8384 |
| src/m85/src/taction.cpp | 4 | 8352 |
| src/ra2/templates/BLIT_INSTANCES.cpp | 44 | 7904 |
| src/m85/src/score.cpp | 2 | 7824 |
| src/m85/src/palette.cpp | 28 | 6624 |
| src/m85/src/fly.cpp | 3 | 6544 |
| src/ra2/templates/FACTORY_INSTANCES.cpp | 46 | 5888 |
| src/m85/src/anim.cpp | 3 | 5376 |
| src/m85/src/infantry.cpp | 4 | 4768 |
| src/m85/src/tactical.cpp | 6 | 4720 |
| src/m85/src/bullet.cpp | 4 | 4576 |
| src/m85/src/display.cpp | 7 | 4464 |
| src/m85/src/wdtmap.cpp | 2 | 3696 |
| src/m85/src/wave.cpp | 2 | 3184 |


## 5. Name differences at the same 1.006 address

- These 16 are rule-meeting rows where their `names.csv` has an inferred name, ours differs, and our function is matched on 1.001.
- Neither side is proven by this. Both names are inferred, except where RTTI or strings decide.
- Several of ours are themselves provisional (`FUN_...`). Theirs are probably better there.

| 1.006 VA (copy) | Our symbol (matched on 1.001) | m85 symbol at that VA (not matched there) |
|---|---|---|
| 0x40a6e0 | `?AudioSetPrimaryFormat@@YIXHHH@Z` | `?Set_Primary_Audio_Format@@YIXHHH@Z` |
| 0x40a770 | `?AudioSetDeviceFormat@@YIXXZ` | `?Restore_Primary_Audio_Format@@YIXXZ` |
| 0x40a820 | `?AudioGetLogVolume@@YIHH@Z` | `?Convert_HMI_To_Direct_Sound_Volume@@YIHH@Z` |
| 0x4106e0 | `??0AbstractTypeClass@@QAE@ABUNoInitClass@@@Z` | `??0AbstractTypeClass@@QAE@ABVNoInitClass@@@Z` |
| 0x480b20 | `?FUN_0048BB40@@YI_NPBVCommandClass@@H@Z` | `?Can_Use_Modified_Key@@YI_NABVCommandClass@@I@Z` |
| 0x480b40 | `?FUN_0048BB60@@YI_NH@Z` | `?Can_Use_Hotkey@@YI_NI@Z` |
| 0x4e11f0 | `??8HashString@@QAE_NABV0@@Z` | `??8HashString@@QBE_NABV0@@Z` |
| 0x617340 | `?Planning_Left_Press@@YI_NVPoint2D@@@Z` | `?Planning_Left_Press@@YG_NHH@Z` |
| 0x623300 | `?Mark_Player_Heard@@YIXH@Z` | `?Stamp_Their_Timing@@YIXH@Z` |
| 0x6ac850 | `??Z?$TPoint3D@H@@QAEABV?$TPoint2D@H@@ABV1@@Z` | `??ZPoint2D@@QAEABV0@ABV0@@Z` |
| 0x6b2df0 | `?Action_Flags@@YIHH@Z` | `?Attaches_To@@YI?AW4AttachType@@W4TActionType@@@Z` |
| 0x7741d0 | `?Get_Pixel@XSurface@@UAEIAAUPoint2D@@@Z` | `?Get_Pixel@XSurface@@UBEHABVPoint2D@@@Z` |
| 0x774220 | `?Put_Pixel@XSurface@@UAE_NAAUPoint2D@@I@Z` | `?Put_Pixel@XSurface@@UAE_NABVPoint2D@@H@Z` |
| 0x774e20 | `?Fill@XSurface@@UAE_NI@Z` | `?Fill@XSurface@@UAE_NH@Z` |
| 0x774f00 | `?Copy_From@XSurface@@UAE_NAAURectangleStruct@@AAVSurface@@0_N2@Z` | `?Blit_From@XSurface@@UAE_NABV?$TRect@H@@ABVSurface@@0_N2@Z` |
| 0x775190 | `?Clip_Rects@@YI_NAAURectangleStruct@@ABU1@01@Z` | `?Blit_Clip@@YI_NAAV?$TRect@H@@ABV1@01@Z` |

## 6. Layouts and RTTI-proven class names
- **Proven by RTTI in both binaries** (details in `fixes.md` entries 10 and 11):
  - `Reestablish` is a class;
  - `UndoInfoStruct` (not DeformUndoStruct);
  - `SpawnControl` is a global struct, not nested;
  - `KamikazeControl` and `Map::AnimationPalette` are structs;
  - `LoadProgressMgr` (not LoadProgressManager).
- **Missing definition:** `Planning_Adjusted_Pixel` (1.006 0x619E00), which planning.h declares (`fixes.md` entry 12).
- **Layouts and vtables:** our 1.001 headers trim the 1.006-only members, virtuals and slots (Waiting, Save_Timing/Restore_Timing, Discard_Packets_To, vt_entry_A0, Index_Of_Connection).
  - That is version-specific (b) and NOT offered.
  - It does show where 1.006 added members after 1.001, which may help them date or justify their `Unknown_Virtual_` placeholders.
