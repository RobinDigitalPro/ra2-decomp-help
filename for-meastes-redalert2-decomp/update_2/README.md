# Update 2 for meastes/redalert2-decomp (2026-11-24)

A follow-up to the eight 1.001 forms in this issue. Since then we matched 17 more functions that your manifests/original_target/non_exact.json still lists, byte for byte on RA2 1.001 (VC6 8168, /O2 /Ob2 /Gr /GR /Gy). Our source for 16 of them is in [update_2](https://github.com/RobinDigitalPro/ra2-decomp-help/tree/main/for-meastes-redalert2-decomp/update_2) (GPL-3.0-or-later). Each file header gives your 1.006 entry, its size, and our 1.001 RVA.

| Your entry | Function | Bytes |
|---|---|---:|
| 0075F530 | CChatEventSink::OnChannelJoin | 5,780 |
| 005919A0 | MechLocomotionClass::Movement_AI | 5,575 |
| 006C5570 | TechnoClass::unknown_6c5570 | 2,998 |
| 005820B0 | MapGeneratorClass::Grow_Water_Region | 2,230 |
| 0047AD00 | CellClass::Place_Veins | 2,191 |
| 0063A880 | Do_Chrono_Reinforcements | 1,567 |
| 004370E0 | BounceClass::AI | 1,448 |
| 004A0050 | DriveLocomotionClass::Draw_Matrix | 1,189 |
| 00676010 | ShipLocomotionClass::Draw_Matrix | 1,189 |
| 0041F1C0 | AlphaShapeClass::Draw_In_Area | 1,048 |
| 006A7E80 | Tactical::Draw_Pixel_Effects | 954 |
| 0070C0A0 | UnVQ1_4x2_Table | 923 |
| 006A8560 | Tactical::Draw_Tiles | 824 |
| 0054FDA0 | MapClass::Compute_Zone_Connections | 804 |
| 00521A90 | IonBlastClass::One_Time | 541 |
| 0060D110 | the PCX loader | 360 |

VoxelAnimClass::VoxelAnimClass (0070C800) also matches on our side; we can send that one separately.

Several bodies (Mech Movement_AI, Place_Veins, IonBlast One_Time, Draw_Pixel_Effects, UnVQ1_4x2_Table) came from gibbo101/ra2-decomp's YR matches, ported to RA2 1.001; credit to them.

Between 1.001 and 1.006 some of these differ in code, so treat them as forms to try, not drop-ins.

Files: snippets/ (16 files of our byte-identical RA2 1.001 source, GPL-3.0-or-later), pairs.json (your entry, name, bytes, our symbol, our RVA, our TU).
