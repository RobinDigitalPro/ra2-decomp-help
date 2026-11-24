# Update 3 for gibbo101/ra2-decomp (2026-11-24)

Thanks for testing update 2. Here is update 3, from the RA2 1.001 side.

**Allocate_Surfaces (your 0x00533FD0): evidence for the flag.** On RA2 1.001 we match it byte for byte (RVA 0x118a70, our init.cpp) as `bool Allocate_Surfaces(const Rect&, const Rect&, const Rect&, const Rect&, bool hidden_first)`. The fifth parameter is a real `bool`: the callers in conquer.cpp, mainopt.cpp, saveload.cpp and startup.cpp pass `false`/`true`. No `Memory_Flag` helper is needed on 1.001. The form that matches computes two named bool locals before the allocations and passes them to the DSurface constructors:
```cpp
bool tile_in_system = !VideoBackBufferAllowed;
bool sidebar_in_system = !Options.AllowVRAMSidebar;
```
The full body is in snippets/0x00533FD0.cpp (similarity 0.977 to your YR body). It is RA2 evidence, not proof for YR, but it suggests the named-local form.

**Pairs for your remaining work list.** Of the 64 YR functions still unmatched on your side, 28 pair with a function we have byte-identical on RA2 1.001 (pairs_unmatched.csv). The strongest leads, with our source in snippets/:
- Create_Region_From_Cell (1.000);
- five OwnerDraw CellData/ColumnData ArrayList members (1.000);
- Allocate_Surfaces (0.977);
- Register_Zone_Connection_Entries (0.961);
- Generate_Random_Map (0.961);
- DriveLocomotionClass::Draw_Matrix (0.959, at both of your addresses);
- ShipLocomotionClass::While_Moving (0.901);
- Is_Same_Cell_Zone (0.894);
- Spark_AI (0.871);
- WinMain (0.847).

**Methods that worked for us this week,** in case they help:
- a victim rule: when good header changes keep breaking the same claimed function, rematch that function instead of rejecting the change;
- three approaches per function group (port / chunk / triangulate against the 1.006 source / sibling / cluster / compiler rules), all tried and scored;
- a link check that showed duplicate definitions between two source trees as the cause of drift.

Your new commits (Find_Path_Regular, Place_Veins, Mech Movement_AI, CacheBMP, ...) helped us directly; six of them now match on RA2 1.001 too. Thanks again.

Files: pairs_unmatched.csv (64 rows, your current unmatched work list filtered against your manifest @1b47a17), pairs_summary.md, snippets/ (15 files of our byte-identical RA2 1.001 source, GPL-3.0-or-later).
